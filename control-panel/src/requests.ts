import { sha256 } from "js-sha256";

function getIpHash(): string {
    // const ip = window.location.hostname;
    const ip = "4.4.4.2";
    return sha256(ip);
}

const defaultBodyArgs = {
    token: getIpHash()
}

export async function handleRequest(route: string, bodyPart: any) {
    try {
        const response = await fetch(`http://4.4.4.1:9000${route}`, {
            method: "POST",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify({
                ...defaultBodyArgs,
                ...bodyPart
            }),
        });
        if (response.ok) {
            return true
        }
        return false
    } catch (error) {
        return false;
    }
}