// api/metrics.js
// Lightweight Vercel performance & submission metrics endpoint.
//
// Reads daily + total counters from KV (if configured) and returns
// a JSON payload the dashboard can poll. No authentication — the
// values are non-sensitive counters. Add basic API-key gating
// (e.g. ?k=<secret>) if the site is public and you want to
// restrict access.
//
// Response shape:
// {
//   configured: boolean,        // whether KV is wired up
//   total:    number | null,    // all-time submissions
//   today:    number | null,    // submissions today (UTC)
//   daily:    { [dateISO]: number },  // last 30 days
//   ts:       string            // server timestamp
// }

import { getCounter, kvAvailable } from '../lib/vercel-kv.js';

export default async function handler(req, res) {
  if (req.method !== 'GET') {
    return res.status(405).json({ error: 'Method not allowed' });
  }

  const configured = kvAvailable();
  const result = {
    configured,
    total: null,
    today: null,
    daily: {},
    ts: new Date().toISOString(),
  };

  if (!configured) {
    // KV not wired up — return zeros so the dashboard still renders
    return res.status(200).json(result);
  }

  // Total + today
  const [total, today] = await Promise.all([
    getCounter('qr_count_total'),
    getCounter(`qr_count_${new Date().toISOString().slice(0, 10)}`),
  ]);
  result.total = total ?? 0;
  result.today = today ?? 0;

  // Last 30 days for a sparkline
  const dailyKeys = [];
  for (let i = 29; i >= 0; i--) {
    const d = new Date(Date.now() - i * 86400000);
    const key = `qr_count_${d.toISOString().slice(0, 10)}`;
    dailyKeys.push([d.toISOString().slice(0, 10), key]);
  }
  const values = await Promise.all(dailyKeys.map(([, k]) => getCounter(k)));
  dailyKeys.forEach(([date, _], i) => {
    result.daily[date] = values[i] ?? 0;
  });

  res.status(200).json(result);
}
