# Revisión de los cambios

La versión nueva se conserva tal como fue enviada. Los siguientes puntos son resultados de la revisión, no correcciones aplicadas.

## Tres cambios principales

1. **Entrada numérica:** `leerEntero()` reemplaza las lecturas directas con `cin` en el menú, la selección de zona y los códigos. Si se escribe texto donde se espera un número, limpia el error y vuelve a pedirlo.
2. **Datos obligatorios y prioridad:** `leerTextoObligatorio()` vuelve a pedir nombres y direcciones vacíos. `seleccionarPrioridad()` restringe la prioridad a Alta, Media o Baja, también al actualizar un pedido.
3. **Orden de la ruta:** `crearRuta()` recorre los pedidos pendientes de la zona tres veces: Alta, Media y Baja. Dentro de cada nivel conserva el orden de registro. `listarRutas()` muestra la prioridad para comprobar el resultado.

El sistema agrupa por zona y prioridad. No calcula distancias ni determina una secuencia geográfica de visitas.
