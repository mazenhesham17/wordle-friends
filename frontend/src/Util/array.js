function lastNelements(arr, n) {
    return arr.slice(-n);
}

function countOccurrences(str, char) {
    if (!str)
        return 0;
    let count = 0;
    for (let i = 0; i < str.length; i++) {
        if (str[i] === char) {
            count++;
        }
    }
    return count;
}

export { lastNelements, countOccurrences }
