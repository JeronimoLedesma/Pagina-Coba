const host = "10.0.3.201";
const port = 1883;
const username = "";
const password = "";

const broker = `ws://${host}:${port}/mqtt`;
const clientID = "web-client";
const topic = "Sensor Infrarrojo";

const client = new Paho.MQTT.Client(broker, clientID);

client.onMessageArrived = (message) => {
    const codigo = message.payloadString;
    manejarCodigoRecibido(codigo);
};

const options = {
    userName: username,
    password: password,
    onSuccess: () => {
        client.subscribe(topic);
    },
    onFailure: (errorMessage) => {
        console.log("Error en la conexión: " + errorMessage.errorMessage);
    }
};

client.connect(options);