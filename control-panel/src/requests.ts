import { sha256 } from "js-sha256";

export async function handleRequest(route: string, bodyPart: any) {
    try {
        const response = await fetch(`http://${window.location.hostname}:9000${route}`, {
            // const response = await fetch(`http://4.4.4.1:9000${route}`, {
            method: "POST",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify({
                token: sha256(window.location.hostname),
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