// api/generate.js
import createQRModule from '../src/qr_module.js';

// Initialize Wasm module outside the handler so it stays warm
const modulePromise = createQRModule();

export default async function handler(req, res) {
  if (req.method !== 'POST') {
    return res.status(405).json({ error: 'Method not allowed' });
  }

  const { text, correctionLevel } = req.body || {};
  if (typeof text !== 'string' || typeof correctionLevel !== 'number') {
    return res.status(400).json({ error: 'Body must be { text: string, correctionLevel: 0-3 }' });
  }

  try {
    const Module = await modulePromise;
    const result = Module.generate(text, correctionLevel);
    
    // Convert from Wasm vector to JS array
    const size = result.size;
    const flat = [];
    for (let i = 0; i < result.data.size(); i++) {
        flat.push(result.data.get(i));
    }
    result.data.delete();

    // Reshape to 2D matrix
    const matrix = [];
    for (let r = 0; r < size; r++) {
      matrix.push(flat.slice(r * size, (r + 1) * size));
    }

    res.status(200).json({ size, matrix });
  } catch (error) {
    console.error(error);
    res.status(500).json({ error: 'Failed to generate QR' });
  }
}