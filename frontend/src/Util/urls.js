function generateUrl() {
    let backendUrl = process.env.REACT_APP_BACKEND_URL;
    if (!backendUrl) {
        throw new Error('REACT_APP_BACKEND_URL is not defined');
    }
    let endpoint = `${backendUrl}/api`;
    for (let i = 0; i < arguments.length; i++) {
        endpoint += '/' + arguments[i];
    }
    return endpoint;
}

function generateSocketUrl() {
    let socket_url = process.env.REACT_APP_SOCKET_URL;
    if (!socket_url) {
        throw new Error('REACT_APP_SOCKET_URL is not defined');
    }
    return socket_url;
}

export { generateUrl , generateSocketUrl};