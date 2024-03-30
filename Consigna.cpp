/*TRABAJO INTEGRADOR GRUPAL
MATERIA: Programacion Imperativa
AÑO: 2021 (primer año de la carrera)


Una de las problemáticas más habituales cuando nos relacionamos mucho tiempo con
mucha gente es que prestamos objetos y luego de un tiempo nos olvidamos qué hicimos
con ellos. En ocasiones recordamos que hicimos un préstamo, pero no sabemos a quién.
El objetivo de este trabajo es realizar un programa que permita a los usuarios registrar,
gestionar y consultar sus préstamos.
En primer, lugar tenemos que identificar las principales entidades que intervienen:
1a) Categorías de objetos prestados, por ejemplo: libros, CD, DVD, Videojuegos, entre
otros objetos.
b) Nómina de personas prestatarias.
c) Los préstamos: van a pertenecer a una categoría y estar asignados a un
prestatario. Además, van a tener un detalle del objeto prestado, para identificarlo.
Por ejemplo, en el caso de un Videojuego, el campo Descripción podrá decir
“Battlefield 4”.
Cada una de las entidades anteriores tienen que ser administradas por el usuario de la
aplicación, es decir, debe poder darlas de alta, modificarlas, eliminarlas y consultarlas.
Se sugiere trabajar con las siguientes entidades y sus respectivas características:
● Categoría, que tendrá un código y una descripción.
● Préstamo, que pertenece a una Categoría, se realizó a un prestatario, tiene una
descripción y un estado.
● Prestatario, que contará con un código, un apellido y un nombre.*/

/*Consideraciones a tener en cuenta a la hora de diseñar el sistema
Categorías:
✔ En el alta, el código de las categorías es autodeterminado por el sistema; es decir,
no debe ser solicitado al usuario, pero sí mostrado al momento del alta. El primer
código asignado por el sistema es el 0 (cero); a partir de ahí, es el mayor código
existente más 1 (uno). La descripción es un campo requerido (no puede quedar
vacío).
✔ Sólo puede ser modificada la descripción (el código, al ser automático, no puede
editarse).
✔ Cuando se elimina una categoría se debe verificar que no haya objetos vinculados
que tengan asignada la categoría y, en caso contrario, impedir la eliminación. El
sistema informará de esta situación al usuario con el mensaje “La categoría no
puede eliminarse debido a que hay préstamos pendientes”. Por ejemplo: si existe
la categoría “videojuegos” y hay algún préstamo de un juego registrado en el
sistema, el usuario no puede eliminar esa categoría a menos que, previamente,
elimine todos los préstamos de videojuegos que existen.
Prestatarios:
✔ En el alta, el código de los prestatarios es autodeterminado por el sistema; es decir,
no debe ser solicitado al usuario, pero sí mostrado al momento del alta. El primer
código asignado por el sistema es el 0 (cero); a partir de ahí es el mayor código
existente más 1 (uno). El apellido y nombres son ambos requeridos (no pueden
quedar vacíos) e, independientemente de cómo los ingrese el usuario, se deben
almacenar con la primera letra en mayúscula. Por ejemplo: nombre: "Agostina” y
apellido: “Ramírez".
✔ Sólo pueden ser modificados el apellido y nombres (el código, al ser automático,
no puede editarse). Tener en cuenta que tanto el apellido como el nombre puede
ser compuesto.
✔ Cuando se elimina un prestatario se debe verificar que no haya objetos vinculados
a ese prestatario y, en caso contrario, impedir la eliminación. El sistema informará
de esta situación al usuario con el mensaje “El prestatario no puede eliminarse
debido a que hay préstamos pendientes”. Por ejemplo: si existe el prestatario
“Agostina Ramírez” y hay algún préstamo hecho a esa persona, el usuario no puede
eliminar a la persona a menos que, previamente, elimine todos los préstamos
hechos a Agostina Ramírez.
Préstamos:
✔ En el alta se debe asignar el código de una categoría (este código constituye el
campo “Categoría” de la entidad Préstamo). Para esto, cuando se realiza la carga se
le debe consultar al usuario: “¿Desea ver las actuales categorías (S/N)?”; sólo se
debe permitir continuar cuando ingrese una de las opciones ofrecidas (en
mayúsculas o minúsculas). Si el usuario selecciona que sí, se listan las categorías y
se deja preparado para que ingrese el código; caso contrario, sólo se deja preparado para que ingrese el código. Se debe chequear que el código ingresado
exista en las categorías (opción válida).
✔ En el alta se debe asignar el código de un prestatario (este código constituye el
campo “Prestatario” de la entidad Préstamo). Para esto, cuando se realiza la carga
se le debe consultar al usuario: “¿Desea ver los actuales prestatarios (S/N)?”; sólo
se debe permitir continuar cuando ingrese una de las opciones ofrecidas (en
mayúsculas o minúsculas). Si el usuario selecciona que sí, se listan los prestatarios
y se deja preparado para que ingrese el código; caso contrario, sólo se deja
preparado para que ingrese el código. Se debe chequear que el código ingresado
exista en los prestatarios (opción válida).
✔ En el alta, la descripción es requerida y, en la modificación, es el único campo que
puede ser modificado (ni la categoría, ni el prestatario ni el estado del préstamo
son editables por el usuario).
✔ El estado de un préstamo indica si el objeto está pendiente de devolución (true) o
si el objeto ya ha sido devuelto (false). Es decir, al dar de alta un nuevo préstamo,
el estado se debe inicializar automáticamente en el valor true.
✔ Cuando un prestatario devuelve un objeto, éste se debe buscar entre los
préstamos existentes pendientes de devolución e indicar que fue devuelto. Para
esto, se imprime en pantalla un listado de prestatarios, con sus códigos, y se ofrece
al usuario ingresar el código de prestatario elegido. El sistema debe, entonces,
listar los préstamos que esa persona tiene pendientes. Cuando se lista el detalle de
los préstamos, el sistema automáticamente les asigna un número delante (a partir
del 1) para que el usuario indique el que desea. Sin embargo, este número es
provisorio; es decir, sólo sirve en este punto del sistema para que el usuario tenga
la posibilidad de seleccionar un préstamo de entre todos los que pertenecen a un
prestatario en particular.
Una vez ingresado el número de préstamo, se debe colocar en “false” el campo Estado del
préstamo, lo que indica que fue devuelto y ya no se encuentra más pendiente de
devolución.
Tanto cuando se ingresa el número del prestatario como cuando se ingresa el número del
objeto, el sistema debe chequear que sea sólo uno de los que se muestran en la pantalla
(opción válida).
El sistema deberá brindar al usuario las siguientes consultas:
✔ Cantidad de préstamos por categoría y el total de préstamos pendientes (sumatoria
de las categorías). Son préstamos pendientes aquellos que tienen el valor “true” en
su Estado.
✔ Dada una categoría, mostrar un listado con la descripción de los préstamos
pendientes y datos del prestatario.
✔ Listar todos los préstamos pendientes, ordenados y agrupados por categoría o por
prestatario. Es decir, el usuario debe poder elegir si desea ver el listado por
categoría o por prestatario con la siguiente pregunta: “¿Clasificar el listado por
Categoría (C) o Prestatario (P)?”; sólo se debe permitir continuar cuando ingrese
una de las opciones ofrecidas (en mayúsculas o minúsculas). Una vez hecho esto,
la opción elegida debe ordenarse alfabéticamente en forma ascendente (por
ejemplo, si las categorías son Videojuegos, Libros, DVD, se ordenarán como: DVD,
Libros, Videojuegos). Por cada una, se listarán todos los préstamos pendientes.
Son préstamos pendientes aquellos que tienen el valor “true” en su Estado. Este
estado no debe mostrarse en el listado. El listado mostrará la descripción,
categoría y datos del prestatario.
✔ Listar todos los prestatarios que tienen préstamos pendientes. El listado debe
mostrar el Nombre, Apellido y cantidad de préstamos pendientes.
El menú del sistema, debe presentarse con la siguiente estructura:
Primer nivel:
1. Administrar y consultar Categorías y Prestatarios
2. Administrar Préstamos
3. Consultar Préstamos
Segundo nivel:
1. Administrar y consultar Categorías y Prestatarios
a) Agregar categoría
b) Modificar categoría
c) Eliminar categoría
d) Agregar prestatario
e) Modificar prestatario
f) Eliminar prestatario
2. Administrar préstamos
a) Agregar préstamo
b) Modificar préstamo
c) Eliminar préstamo
d) Devolver préstamo
3. Consultar Préstamos
a) Cantidad de objetos prestados por categoría
b) Listado de préstamos por categoría
c) Listado de préstamos ordenados por categoría o prestatario
d) Listar todos los prestatarios que tienen al menos un objeto prestado
*/