

#include "QR_Generator.hpp"





uint8_t QR_Generator::gf_mul(uint8_t a, uint8_t b) {
    if (a == 0 || b == 0) return 0;
    return gf_exp[gf_log[a] + gf_log[b]];
}
std::vector<uint8_t> QR_Generator::generate_rs_polynomial(int num_ec_codewords) {
    std::vector<uint8_t> gen = {1};
    for (int i = 0; i < num_ec_codewords; ++i) {
        uint8_t alpha_i = gf_exp[i];
        std::vector<uint8_t> next_gen(gen.size() + 1, 0);
        for (size_t j = 0; j < gen.size(); ++j) {
            next_gen[j] ^= gen[j];
            next_gen[j + 1] ^= gf_mul(gen[j], alpha_i);
        }
        gen = next_gen;
    }
    return gen;
}
std::vector<uint8_t> QR_Generator::compute_ec_codewords(const std::vector<uint8_t>& data_block, int num_ec_codewords) {
    std::vector<uint8_t> gen = generate_rs_polynomial(num_ec_codewords);
    std::vector<uint8_t> message = data_block;
    message.resize(data_block.size() + num_ec_codewords, 0);
    for (size_t i = 0; i < data_block.size(); ++i) {
        uint8_t coef = message[i]; 
        if (coef != 0) {
            for (size_t j = 0; j < gen.size(); ++j) {
                message[i + j] ^= gf_mul(gen[j], coef);
            }
        }
    }
    std::vector<uint8_t> ec_codewords(message.end() - num_ec_codewords, message.end());
    return ec_codewords;
}
void QR_Generator::pushBits(std::vector<bool>& bitStream, uint16_t value, int length) {
    for (int i = length - 1; i >= 0; --i) {
        bitStream.push_back((value >> i) & 1);
    }
}

long QR_Generator::calculate_penalty_score(const std::vector<std::vector<int>>& grid) {
    long score = 0;
    int QRsize = grid.size();
    for (int i = 0; i < QRsize; ++i) {
        int run_color_h = -1, run_length_h = 0;
        int run_color_v = -1, run_length_v = 0;
        for (int j = 0; j < QRsize; ++j) {
            if (grid[i][j] == run_color_h) {
                run_length_h++;
                if (run_length_h == 5) score += 3;
                else if (run_length_h > 5) score += 1;
            } else {
                run_color_h = grid[i][j];
                run_length_h = 1;
            }
            if (grid[j][i] == run_color_v) {
                run_length_v++;
                if (run_length_v == 5) score += 3;
                else if (run_length_v > 5) score += 1;
            } else {
                run_color_v = grid[j][i];
                run_length_v = 1;
            }
        }
    }
    for (int r = 0; r < QRsize - 1; ++r) {
        for (int c = 0; c < QRsize - 1; ++c) {
            int color = grid[r][c];
            if (color == grid[r][c + 1] && 
                color == grid[r + 1][c] && 
                color == grid[r + 1][c + 1]) {
                score += 3;
            }
        }
    }
    auto is_dark = [&](int r, int c) {
        if (r < 0 || r >= QRsize || c < 0 || c >= QRsize) return false;
        return grid[r][c] == 1;
    };
    auto is_light = [&](int r, int c) {
        if (r < 0 || r >= QRsize || c < 0 || c >= QRsize) return true; 
        return grid[r][c] == 0;
    };
    for (int r = 0; r < QRsize; ++r) {
        for (int c = 0; c < QRsize; ++c) {
            if (is_dark(r, c) && is_light(r, c+1) && is_dark(r, c+2) && 
                is_dark(r, c+3) && is_dark(r, c+4) && is_light(r, c+5) && is_dark(r, c+6)) {
                if ((is_light(r, c-1) && is_light(r, c-2) && is_light(r, c-3) && is_light(r, c-4)) ||
                    (is_light(r, c+7) && is_light(r, c+8) && is_light(r, c+9) && is_light(r, c+10))) {
                    score += 40;
                }
            }
            if (is_dark(r, c) && is_light(r+1, c) && is_dark(r+2, c) && 
                is_dark(r+3, c) && is_dark(r+4, c) && is_light(r+5, c) && is_dark(r+6, c)) {
                if ((is_light(r-1, c) && is_light(r-2, c) && is_light(r-3, c) && is_light(r-4, c)) ||
                    (is_light(r+7, c) && is_light(r+8, c) && is_light(r+9, c) && is_light(r+10, c))) {
                    score += 40;
                }
            }
        }
    }
    int darkCount = 0;
    int totalCount = QRsize * QRsize;
    for (int r = 0; r < QRsize; ++r) {
        for (int c = 0; c < QRsize; ++c) {
            if (grid[r][c] == 1) darkCount++;
        }
    }
    int darkPercent = (darkCount * 100) / totalCount;
    int rating = std::abs(darkPercent - 50) / 5;
    score += rating * 10;
    return score;
}
void QR_Generator::alignment(std::vector<std::vector<int>>& QRdata, int cx, int cy) {
    for (int r = -2; r <= 2; ++r) {
        for (int c = -2; c <= 2; ++c) {
            if (QRdata[cx + r][cy + c] != 2) return;
        }
    }
    for (int r = -2; r <= 2; ++r) {
        for (int c = -2; c <= 2; ++c) {
            int dist = std::max(std::abs(r), std::abs(c));
            QRdata[cx + r][cy + c] = (dist == 1) ? 0 : 1;
        }
    }
}
void QR_Generator::placeAlignmentPatterns(std::vector<std::vector<int>>& QRdata, int version) {
    if (version < 2) return;
    static const std::vector<int> alignPos[41] = {
        {}, 
        {}, 
        {6, 18}, {6, 22}, {6, 26}, {6, 30}, {6, 34},                             // V2 - V6
        {6, 22, 38}, {6, 24, 42}, {6, 26, 46}, {6, 28, 50}, {6, 30, 54},         // V7 - V11
        {6, 32, 58}, {6, 34, 62}, {6, 26, 46, 66}, {6, 26, 48, 70},              // V12 - V15
        {6, 26, 50, 74}, {6, 30, 54, 78}, {6, 30, 56, 82}, {6, 30, 58, 86},      // V16 - V19
        {6, 34, 62, 90}, {6, 28, 50, 72, 94}, {6, 26, 50, 74, 98},               // V20 - V22
        {6, 30, 54, 78, 102}, {6, 28, 54, 80, 106}, {6, 32, 58, 84, 110},        // V23 - V25
        {6, 30, 58, 86, 114}, {6, 34, 62, 90, 118}, {6, 26, 50, 74, 98, 122},    // V26 - V28
        {6, 30, 54, 78, 102, 126}, {6, 26, 52, 78, 104, 130},                    // V29 - V30
        {6, 30, 56, 82, 108, 134}, {6, 34, 60, 86, 112, 138},                    // V31 - V32
        {6, 30, 58, 86, 114, 142}, {6, 34, 62, 90, 118, 146},                    // V33 - V34
        {6, 30, 54, 78, 102, 126, 150}, {6, 24, 50, 76, 102, 128, 154},          // V35 - V36
        {6, 28, 54, 80, 106, 132, 158}, {6, 32, 58, 84, 110, 136, 162},          // V37 - V38
        {6, 26, 54, 82, 110, 138, 166}, {6, 30, 58, 86, 114, 142, 170}           // V39 - V40
    };
    const auto& coords = alignPos[version];
    for (int r : coords) {
        for (int c : coords) {
            alignment(QRdata, r, c);
        }
    }
}
void QR_Generator::drawFinder(std::vector<std::vector<int>>& QRdata,int QRsize, int startR, int startC) {
    for (int r = -1; r <= 7; ++r) {
        for (int c = -1; c <= 7; ++c) {
            int actualR = startR + r;
            int actualC = startC + c;
            if (actualR < 0 || actualR >= QRsize || actualC < 0 || actualC >= QRsize) continue;
            if (r == -1 || r == 7 || c == -1 || c == 7) {
                QRdata[actualR][actualC] = 0;
            }
            else if (r == 0 || r == 6 || c == 0 || c == 6) {
                QRdata[actualR][actualC] = 1;
            }
            else if (r == 1 || r == 5 || c == 1 || c == 5) {
                QRdata[actualR][actualC] = 0;
            }
            else {
                QRdata[actualR][actualC] = 1;
            }
        }
    }
}
void QR_Generator::updateVersionAndSize(int corlvl, int& strsize, int& version) {
    static constexpr std::array<std::array<int, 40>, 4> limits = {{
        {17, 32, 53, 78, 106, 134, 154, 192, 230, 271, 321, 367, 425, 458, 520, 586, 644, 718, 792, 858, 929, 1003, 1091, 1171, 1273, 1367, 1465, 1528, 1628, 1732, 1840, 1952, 2068, 2188, 2303, 2431, 2563, 2699, 2809, 2953},
        {14, 26, 42, 62, 84, 106, 122, 152, 180, 213, 251, 287, 331, 362, 412, 450, 504, 560, 624, 666, 711, 779, 857, 911, 997, 1059, 1125, 1190, 1264, 1370, 1452, 1538, 1628, 1722, 1809, 1911, 1989, 2099, 2212, 2331},
        {11, 20, 32, 46, 60, 74, 86, 108, 130, 151, 177, 203, 241, 258, 292, 322, 364, 394, 442, 482, 509, 565, 611, 661, 715, 751, 805, 868, 908, 982, 1030, 1112, 1168, 1228, 1283, 1351, 1423, 1499, 1579, 1663},
        {7, 14, 24, 34, 44, 58, 64, 84, 98, 119, 137, 155, 177, 194, 220, 250, 280, 310, 338, 382, 403, 439, 461, 511, 535, 593, 625, 658, 698, 742, 790, 842, 898, 958, 983, 1051, 1093, 1139, 1219, 1273}
    }};
    if (corlvl >= 0 && corlvl < 4) {
        const auto& row = limits[corlvl];
    
        auto it = std::lower_bound(row.begin(), row.end(), strsize);
        if (it != row.end()) {
            version = std::distance(row.begin(), it) + 1;
            strsize = *it;                                
        }
    }
}
QR_Generator::QR_Generator(){    
    int val = 1;
    for (int n = 0; n < 255; ++n) {
        gf_exp[n] = val;
        gf_log[val] = n;
        val <<= 1;
        if (val >= 256) {
            val ^= 285;
        }
    }
    for (int n = 255; n < 512; ++n) {
        gf_exp[n] = gf_exp[n - 255];
    }   
}
std::vector<std::vector<int>> QR_Generator::GenerateQR(std::string QRchar,int corlvl){
    int strsize=0,QRsize=21,version=1;
    strsize = QRchar.size();
    updateVersionAndSize(corlvl,strsize,version);
    //Setting QRSize Respect to version
    QRsize = 21 + (version - 1) * 4;
    std::vector <std::vector<int>> QRdata(QRsize,std::vector<int> (QRsize,2));
    //Finder patterns
    drawFinder(QRdata, QRsize, 0, 0);
    drawFinder(QRdata, QRsize, 0, QRsize - 7);
    drawFinder(QRdata, QRsize, QRsize - 7, 0);
    //Alignment Patterns
    placeAlignmentPatterns(QRdata, version);
    QRdata[4 * version + 9][8] = 1;
    //Timing pattern
   for(int i = 0; i < QRsize; i++){
        if (QRdata[6][i] == 2) QRdata[6][i] = (i % 2 == 0) ? 1 : 0;
        if (QRdata[i][6] == 2) QRdata[i][6] = (i % 2 == 0) ? 1 : 0;
    }
    BlockSpec blockSpec = QR_BLOCK_TABLE[version][corlvl];
    std::vector<uint8_t> data_ ;
    std::vector<bool> bitStream;
    pushBits(bitStream, 4, 4);
    if(version<10 && version>0){pushBits(bitStream,QRchar.size(),8);}
    else if(version>=10 && version<27){pushBits(bitStream,QRchar.size(),12);}
    else{pushBits(bitStream,QRchar.size(),16);}
    for (char c : QRchar) pushBits(bitStream, c, 8);
    int capacityBits = blockSpec.totalDataBytes * 8;
    int terminatorZeros = std::min(4, capacityBits - (int)bitStream.size());
    if (terminatorZeros > 0) {
        pushBits(bitStream, 0, terminatorZeros);
    }
    while (bitStream.size() % 8 != 0) {
        bitStream.push_back(0);
    }
    for (size_t i = 0; i < bitStream.size(); i += 8) {
        uint8_t byte = 0;
        for (int b = 0; b < 8; ++b) {
            byte = (byte << 1) | bitStream[i + b];
        }
        data_.push_back(byte);
    }
    bool padEC = true;
    while (data_.size() < blockSpec.totalDataBytes) {
        data_.push_back(padEC ? 236 : 17);
        padEC = !padEC;
    }
    std::vector<std::vector<uint8_t>> data_blocks;
    int cursor = 0;
    // Extract Group 1 blocks
    for (int i = 0; i < blockSpec.g1Blocks; ++i) {
        data_blocks.push_back(std::vector<uint8_t>(
            data_.begin() + cursor, 
            data_.begin() + cursor + blockSpec.g1Bytes
        ));
        cursor += blockSpec.g1Bytes;
    }
    // Extract Group 2 blocks (if any)
    for (int i = 0; i < blockSpec.g2Blocks; ++i) {
        data_blocks.push_back(std::vector<uint8_t>(
            data_.begin() + cursor, 
            data_.begin() + cursor + blockSpec.g2Bytes
        ));
        cursor += blockSpec.g2Bytes;
    }
    std::vector<std::vector<uint8_t>> ec_blocks;
    for (const auto& block : data_blocks) {
        ec_blocks.push_back(compute_ec_codewords(block, blockSpec.ecPerBlock));
    }
    std::vector<uint8_t> final_interleaved_bytes;
    // Interleave Data Bytes
    size_t max_data_len = std::max(blockSpec.g1Bytes, blockSpec.g2Bytes);
    for (size_t col = 0; col < max_data_len; ++col) {
        for (size_t row = 0; row < data_blocks.size(); ++row) {
            if (col < data_blocks[row].size()) {
                final_interleaved_bytes.push_back(data_blocks[row][col]);
            }
        }
    }
    //  Interleave Error Correction Bytes
    for (size_t col = 0; col < blockSpec.ecPerBlock; ++col) {
        for (size_t row = 0; row < ec_blocks.size(); ++row) {
            final_interleaved_bytes.push_back(ec_blocks[row][col]);
        }
    }
    std::vector<bool> final_bitstream;
    // Convert interleaved bytes to bits
    for (uint8_t byte : final_interleaved_bytes) {
        for (int b = 7; b >= 0; --b) {
            final_bitstream.push_back((byte >> b) & 1);
        }
    }
    int remainder_bits = 0;
    if (version >= 7 && version <= 13) remainder_bits = 7;
    else if (version >= 14 && version <= 20) remainder_bits = 3;
    else if (version >= 21 && version <= 27) remainder_bits = 4;
    else if (version >= 28 && version <= 34) remainder_bits = 3;
    for (int i = 0; i < remainder_bits; ++i) {
        final_bitstream.push_back(0); // Add a 0 bit
    }
    //Reserve the Format Information Area 
    for (int i = 0; i <= 8; ++i) {
        if (i == 6) continue; 
        QRdata[8][i] = 0; 
        QRdata[i][8] = 0; 
    }
    for (int i = 0; i < 7; ++i) {
        QRdata[QRsize - 1 - i][8] = 0; 
    }
    for (int i = 0; i < 8; ++i) {
        QRdata[8][QRsize - 8 + i] = 0; 
    }
    // Reserve the Version Information Area 
    if (version >= 7) {
        for (int r = QRsize - 11; r <= QRsize - 9; ++r) {
            for (int c = 0; c <= 5; ++c) {
                QRdata[r][c] = 0; 
            }
        }
        for (int r = 0; r <= 5; ++r) {
            for (int c = QRsize - 11; c <= QRsize - 9; ++c) {
                QRdata[r][c] = 0; 
            }
        }
    }
    //Mask
    std::vector<std::vector<int>> baseMatrix = QRdata;
    std::vector<std::vector<std::vector<int>>> maskedGrids(8, baseMatrix);
    int bestMask = 0;
    long lowestPenalty = std::numeric_limits<long>::max();
    std::vector<std::vector<int>> bestGrid;
    std::vector<std::vector<int>> unmaskedGrid = baseMatrix;
    int bitIndex = 0;
    int maxBits = final_bitstream.size();
    bool movingUp = true;
    int c = QRsize - 1;
    int r = QRsize - 1;
    while (c > 0) {
        if (c == 6) {
            c--;
        }
        for (int i = 0; i < 2; ++i) {
            int col = c - i; 
                    if (unmaskedGrid[r][col] == 2) {
                            if (bitIndex < maxBits) {
                    unmaskedGrid[r][col] = final_bitstream[bitIndex];
                    bitIndex++;
                } else {
                    unmaskedGrid[r][col] = 0; 
                }
            }
        }
        if (movingUp) {
            r--;
            if (r < 0) {
                r = 0;
                movingUp = false;
                c -= 2;
            }
        } else {
            r++;
            if (r >= QRsize) {
                r = QRsize - 1;
                movingUp = true;
                c -= 2;
            }
        }
    }
    for (int mask = 0; mask < 8; ++mask) {
        std::vector<std::vector<int>> testGrid = unmaskedGrid;
        for (int r = 0; r < QRsize; ++r) {
            for (int c = 0; c < QRsize; ++c) {
                if (baseMatrix[r][c] == 2) {
                    bool invert = false;
                    switch (mask) {
                        case 0: invert = (r + c) % 2 == 0; break;
                        case 1: invert = (r % 2) == 0; break;
                        case 2: invert = (c % 3) == 0; break;
                        case 3: invert = (r + c) % 3 == 0; break;
                        case 4: invert = ((r / 2) + (c / 3)) % 2 == 0; break;
                        case 5: invert = ((r * c) % 2) + ((r * c) % 3) == 0; break;
                        case 6: invert = (((r * c) % 2) + ((r * c) % 3)) % 2 == 0; break;
                        case 7: invert = (((r + c) % 2) + ((r * c) % 3)) % 2 == 0; break;
                    }
                    if (invert) {
                        testGrid[r][c] ^= 1; 
                    }
                }
            }
        }
        long penalty = calculate_penalty_score(testGrid); 
        if (penalty < lowestPenalty) {
            lowestPenalty = penalty;
            bestMask = mask;
            bestGrid = testGrid;
        }
    }
    int ecFormatBits[4] = {1, 0, 3, 2}; 
    int formatData = (ecFormatBits[corlvl] << 3) | bestMask;
    int formatBCH = formatData << 10;
    for (int i = 4; i >= 0; --i) {
        if ((formatBCH >> (i + 10)) & 1) {
            formatBCH ^= (0x537 << i); // 0x537 is the generator polynomial 10100110111
        }
    }
    int formatBits = ((formatData << 10) | formatBCH) ^ 0x5412;
    for (int i = 0; i < 15; ++i) {
        bool bit = (formatBits >> (14 - i)) & 1;
        if (i < 6) bestGrid[8][i] = bit;
        else if (i == 6) bestGrid[8][7] = bit;     
        else if (i == 7) bestGrid[8][8] = bit;
        else if (i == 8) bestGrid[7][8] = bit;
        else bestGrid[14 - i][8] = bit;            
        if (i < 7) bestGrid[QRsize - 1 - i][8] = bit;
        else bestGrid[8][QRsize - 15 + i] = bit;
    }
    if (version >= 7) {
        int versionBCH = version << 12;
        for (int i = 5; i >= 0; --i) {
            if ((versionBCH >> (i + 12)) & 1) {
                versionBCH ^= (0x1F25 << i); // 0x1F25 is the generator 1111100100101
            }
        }
        int versionBits = (version << 12) | versionBCH;
            for (int i = 0; i < 18; ++i) {
            bool bit = (versionBits >> i) & 1; 
            int r = i / 3;
            int c = i % 3;            
            bestGrid[QRsize - 11 + c][r] = bit;
            bestGrid[r][QRsize - 11 + c] = bit;
        }
    }
    return bestGrid;
}

