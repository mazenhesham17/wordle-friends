function generateUrl() {
    let backendUrl = process.env.REACT_APP_BACKEND_URL;
    if (!backendUrl) {
        // running in local enviroment
        backendUrl = 'http://localhost:4000';
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
        // running in local enviroment
        socket_url = 'ws://localhost:8080';
    }
    return socket_url;
}

export { generateUrl , generateSocketUrl};