// lib/vercel-kv.js
// Vercel KV (Upstash Redis) counter helper — zero npm dependencies.
// Uses the Upstash REST API (global fetch, available in Vercel Node/Edge functions).
// Every call is a no-op that returns null when unconfigured, so the app
// works identically with or without KV.
//
// To activate counters, add these environment variables in the Vercel
// dashboard (Project → Settings → Environment Variables):
//   QR_KV_REST_URL    = https://<your-instance>.upstash.io
//   QR_KV_REST_TOKEN  = <your token>
//
// Daily counter keys auto-expire after 40 days; the total key never expires.

const DAY = 86400; // 24h in seconds

let restUrl = null;
let restToken = null;

function init() {
  if (restUrl) return;
  restUrl = process.env.QR_KV_REST_URL || null;
  restToken = process.env.QR_KV_REST_TOKEN || null;
}

/** True when a KV backend is configured. */
export function kvAvailable() {
  init();
  return !!(restUrl && restToken);
}

async function call(path, body, method = 'POST') {
  if (!kvAvailable()) return null;
  try {
    const res = await fetch(`${restUrl}${path}`, {
      method,
      headers: {
        Authorization: `Bearer ${restToken}`,
        'Content-Type': 'application/json',
      },
      body: body === undefined ? undefined : JSON.stringify(body),
    });
    if (!res.ok) return null;
    const json = await res.json();
    return json.result ?? null;
  } catch {
    return null;
  }
}

/**
 * INCR a counter. Optional ttlSeconds sets an expiry on the key
 * (ignored if the key already exists without an expiry).
 */
export async function incrementCounter(key, ttlSeconds = 0) {
  const args = [key, 1];
  if (ttlSeconds > 0) args.push('EX', ttlSeconds);
  const v = await call('/incr', args);
  return v == null ? null : Number(v);
}

/** GET a counter value; null if unset or unconfigured. */
export async function getCounter(key) {
  const v = await call('/get', [key]);
  return v == null ? null : Number(v);
}

/**
 * Convenience: increment today's daily key (auto-expires in 40 days)
 * and the all-time total key. Fire-and-forget safe.
 */
export async function countSubmission() {
  const today = `qr_count_${new Date().toISOString().slice(0, 10)}`;
  await Promise.all([
    incrementCounter(today, 40 * DAY),
    incrementCounter('qr_count_total'),
  ]);
}
