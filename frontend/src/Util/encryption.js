async function hashPassword(plaintextPassword) {
    const encoder = new TextEncoder();
    const data = encoder.encode(plaintextPassword);
    // Use the SubtleCrypto API to hash the password
    const hashBuffer = await crypto.subtle.digest('SHA-256', data);
    // Convert the hash buffer to a hexadecimal string
    const hashArray = Array.from(new Uint8Array(hashBuffer));
    const hashedPassword = hashArray.map(byte => byte.toString(16).padStart(2, '0')).join('');
    return hashedPassword;
}

export { hashPassword };