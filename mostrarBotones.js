function manejarCodigoRecibido(codigo) {
    const mensajeBox = document.getElementById("mensaje");

    switch (codigo) {
        case "1":
            mensajeBox.textContent = "Botón 1";
            break;
        case "2":
            mensajeBox.textContent = "Botón 2";
            break;
        case "3":
            mensajeBox.textContent = "Botón 3";
            break;
        default:
            mensajeBox.textContent = "Código no reconocido";
            break;
    }
}