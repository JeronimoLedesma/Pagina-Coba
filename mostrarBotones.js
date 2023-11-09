function manejarCodigoRecibido(codigo) {
    const botonPresionado = document.getElementById("botonPresionado");

    if (codigo) {
        switch (codigo) {
            case "4278238976":
                botonPresionado.textContent = "Botón Prendido/Apagado";
                break;
            case "4261527296":
                botonPresionado.textContent = "Botón Vol+";
                break;
            case "4127833856":
                botonPresionado.textContent = "Botón Vol-";
                break;
            case "4244815616":
                botonPresionado.textContent = "Botón Func/Stop";
                break;
            case "4211392256":
                botonPresionado.textContent = "Botón |<<";
                break;
            case "4194680576":
                botonPresionado.textContent = "Botón >||";
                break;
            case "4177968896":
                botonPresionado.textContent = "Botón >>|";
                break;
            case "4144545536":
                botonPresionado.textContent = "Botón Arriba";
                break;
            case "4060987136":
                botonPresionado.textContent = "Botón EQ";
                break;
            case "4044275456":
                botonPresionado.textContent = "ST/REPT";
                break;
            case "4077698816":
                botonPresionado.textContent = "Botón 0";
                break;
            case "4010852096":
                botonPresionado.textContent = "Botón 1";
                break;
            case "3994140416":
                botonPresionado.textContent = "Botón 2";
                break;
            case "3977428736":
                botonPresionado.textContent = "Botón 3";
                break;
            case "3944005376":
                botonPresionado.textContent = "Botón 4";
                break;
            case "3927293696":
                botonPresionado.textContent = "Botón 5";
                break;
            case "3910582016":
                botonPresionado.textContent = "Botón 6";
                break;
            case "3877158656":
                botonPresionado.textContent = "Botón 7";
                break;
            case "3860446976":
                botonPresionado.textContent = "Botón 8";
                break;
            case "3843735296":
                botonPresionado.textContent = "Botón 9";
                break;


            default:
                botonPresionado.textContent = "Código no reconocido";
                break;
        }

        const fecha = new Date().toLocaleString();
        agregarAlHistorial(fecha,botonPresionado.textContent);
    } else {
        botonPresionado.textContent = "Mensaje vacío o no válido";
    }
}


function agregarAlHistorial(fecha, boton) {
    const historial = document.getElementById("historial");
    const fila = historial.insertRow();
    const celdaFecha = fila.insertCell(0);
    const celdaBoton = fila.insertCell(1);
    celdaFecha.innerHTML = fecha;
    celdaBoton.innerHTML = boton;
}