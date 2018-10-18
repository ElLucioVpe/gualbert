#include "header.h"

//Inserto Tabla
tipoRet insertoTabla(tabla *tabl, string nombre){
    tabla auxTable;
    auxTable = *tabl;

    if(nombre != "") {
        while(!esVacia(auxTable)) {
            if(auxTable->nombre == nombre) {
                return error; // Ya existe una tabla con ese nombre
            }
            auxTable = auxTable->ptrtabla;
        }

        // Crea nueva tabla
        tabla tablon;
        tablon=*tabl;
        tablon=insertarTabla(tablon,nombre);
        *tabl=tablon;

        return ok;
    } else {
        return error;
    }

}

tabla insertarTabla(tabla tabl, string name){
    tabla nuevatabla;
    nuevatabla = new _tabla;
    nuevatabla->nombre=name;
    nuevatabla->ptrtabla=NULL;

    if(esVacia(tabl)) {
        // Si es vacia la agrega  al principio
        //nuevatabla->ptrtabla=tabl;
        tabl=nuevatabla;
    } else {
        // Recorre la lista hasta llegar a la ultima tabla
        tabla auxTable;
        auxTable = tabl;

        while(!esVacia(auxTable)) {
            if(esVacia(auxTable->ptrtabla)) {
                auxTable->ptrtabla = nuevatabla; // Asigna la tabla al final
                break;
            }
            auxTable = auxTable->ptrtabla; // Sigue buscando
        }
    }

    return tabl;
}

//Inserto columna
tipoRet insertoColumna(tabla *tabl, string nombreTabla, string nombreColumna){
    tabla auxTable;
    auxTable = *tabl;

    if(nombreColumna == "" || nombreTabla == "") {
        return error;
    }

    if(!esVacia(auxTable)) {

        while(!esVacia(auxTable)) {

            if(auxTable->nombre == nombreTabla) {

                columna auxCol;
                auxCol = auxTable->columna;

                // Chequea que la primera fila de la primera columna (si existe) no sea vacia
                if(!esVacia(auxCol)) {
                    fila auxFila;
                    auxFila = auxCol->fila;

                    if(!esVacia(auxCol->fila)) {
                        return error; // La tabla tiene por lo menos una tupla
                    }
                }

                // Verifica que no exista columna con ese nombre
                while(!esVacia(auxCol)) {
                    if(auxCol->nombreCol == nombreColumna) {
                        return error; // Ya existe una columna con ese nombre
                    }
                    auxCol = auxCol->sgtColumna;
                }

                // Crea nueva tabla
                tabla tablon;
                tablon=*tabl;
                tablon=insertarColumna(tablon, auxTable, nombreColumna);

                *tabl=tablon;
                return ok;
            }

            auxTable = auxTable->ptrtabla;
        }

        return error; // No existe una tabla con el nombre dado
    } else {
        return error; // La tabla es vacia
    }
}

tabla insertarColumna(tabla tabl, tabla auxTable, string nombreColumna) {
    // Declaramos la nueva columna
    columna newCol = new _columna;
    newCol->nombreCol = nombreColumna;

    if(esVacia(auxTable->columna)) {
        auxTable->columna = newCol;
    } else {
        columna auxCol = auxTable->columna;

        while(!esVacia(auxCol)) {
            if(esVacia(auxCol->sgtColumna)) {
                auxCol->sgtColumna = newCol;
                return tabl;
            }
            auxCol = auxCol->sgtColumna;
        }
    }
    return tabl;
}

//Inserto Dato
tipoRet insertoDato(tabla *tabl, string nombreTabla, string dato){

    if(nombreTabla == "" || dato == "") {
        return error;
    }

    tabla tablon;
    tablon=*tabl;

    int numDats=0;
    int numCols=0;

    tabla auxTable;
    auxTable = *tabl;

    string primaryKey;
    std::istringstream ss(dato);
    std::string token;

    std::istringstream dd(dato);
    std::string tokenx;

    //Verifico numero de datos que se quieren insertar
     while(std::getline(dd, tokenx, ':')) {
           numDats++;
        }
        numCols=cuentoColumnas(nombreTabla,auxTable);
    ////

    while(!esVacia(auxTable)){
        if(auxTable->nombre == nombreTabla) {

            if(std::getline(ss, token, ':')) {
                primaryKey = token;
            }

            if(!verificoDuplicadoFila(tabl, nombreTabla, primaryKey)) {
                tablon=insertarDato(tablon, auxTable, dato);
                *tabl=tablon;
                return ok;
            } else {
                return error;
            }
        if(!verificoDuplicadoFila(tabl, nombreTabla, primaryKey)) {

                if(numCols==numDats){
                    tablon=insertarDato(tablon, auxTable, dato);
                   *tabl=tablon;
                   return ok;
                }
                else {
                cout << "No tiene el mismo numero de tuplas que de columnas";
                return error;
               }

        } else {
            cout << "Pk multiplicada";
            return error;
        }
        auxTable = auxTable->ptrtabla;
    }
    return error; // No se encontro la tabla
}

tabla insertarDato(tabla tabl, tabla tablaInsertarDato, string dato){
    tabla tablaAux;
    tablaAux = tablaInsertarDato;

    columna col;
    col = new _columna;
    col = tablaAux->columna;

    std::istringstream ss(dato);
    std::string token;

    // Empieza a recorrer columnas
    while(!esVacia(col)) {
        // Empieza a recorrer datos
        while(std::getline(ss, token, ':')) {

            fila newDato; // Genera nueva fila
            newDato = new _fila;
            newDato->dato = token;
            newDato->sgtFila=NULL;

            fila fil; // Asigna fil a la columna
            fil = new _fila;
            fil = col->fila;

            //cout << col->nombreCol << " // " << token << endl;

            if(esVacia(fil)) {
                col->fila = newDato;
            } else {
                //newDato->sgtFila = col->fila;
                while(!esVacia(fil)) {
                    if(esVacia(fil->sgtFila)) {
                        fil->sgtFila = newDato;
                        break;
                    }
                    fil = fil->sgtFila;
                }
            }

            col = col->sgtColumna;
        }
            return tabl;

    }

}

///Inicializar tabla
void creoTabla(tabla **tabl){

    tabla nuevatabla;
    nuevatabla = new _tabla;

    nuevatabla -> ptrtabla=NULL; //1 -> null
    **tabl = nuevatabla;
}

tipoRet inicioTabla(tabla *tabl){

    creoTabla(&tabl);

    return ok;
}


///Muestro Retorno
void muestroR(tipoRet resultado){

    switch(resultado){

    case 0 :
    cout << "ok";
    break;

    case 1:
    cout << "Error";
    break;

    case 2:
    cout << "No Implementado";
    break;

    }

}

bool esVacia(tabla tabl) {
    if(tabl == NULL || tabl->nombre == ""){
        return true;

    }else{
         return false;

    }
}

bool esVacia(columna column) {
    if(column == NULL || column->nombreCol == ""){
        return true;

    }else{
         return false;

    }
}

bool esVacia(fila aux) {
    if(aux == NULL || aux->dato == ""){
        return true;

    }else{
         return false;

    }
}

tipoRet mostrarListaRet(tabla l){
    if(!esVacia(l)){
        mostrarListaRecur(l);
        // Finaliza
        cout << "Fin" << endl;
        return ok;
    }else{
        return error;
        cout << "Empty";
    }
}

void mostrarListaRecur(tabla l){
    columna col;
    col = new _columna;

    fila fil;
    fil = new _fila;

    if (!esVacia(l)){

    // Escribe nombre de la tabla
        cout << endl;
        cout << "-----------------" << endl;
        cout << l->nombre << endl;

    // Chequea cada columna
        col = l->columna;

        if(!esVacia(l->columna)) {
            // Muestra el nombre de las columnas
            while(!esVacia(col)) {
                cout << col->nombreCol << " : ";
                col = col->sgtColumna;
            }
            cout << endl;

            col = l->columna;
            fila ultimaFila = col->fila;
            int i = 0;

            // Recorre las filas siguientes
            col = l->columna;
            if(ultimaFila==NULL){
            cout << "No hay Datos";
            }else{

            while(!esVacia(ultimaFila->sgtFila)) { // Recorre hasta que el siguiente de alguna columna sea NULL -BEBETO si hace eso y queda uno solo nunca entra
                //cout << "IMPORTANTE" << i << endl;
            col = l->columna;

                while(!esVacia(col)) { // Recorre todas las columnas

                    int contar = 0;
                    fila fil = col->fila;

                    while(contar<i) { // Recorre todas las filas
                        fil = fil->sgtFila;
                        contar++;
                    }

                    cout << fil->dato;
                    ultimaFila = fil;
                    col = col->sgtColumna;
                }
                i++;
                cout << endl;

            }

            if((i==0)&&(!esVacia(ultimaFila))){ //Hay una sola fila. nunca entro al while de arriba por eso esta i en 0

            col = l->columna;

            while(!esVacia(col)) {//REcorre Columns
            fila fil = col->fila;//Toma primer fila de column
            cout << fil->dato;
            col = col->sgtColumna;

            }

            }
            }


            cout << endl;
            cout << "-----------------" << endl;
        } else {
            cout << "No existen columnas en esta tabla" << endl;
            cout << "-----------------" << endl;

        }

    // Chequea la tabla siguiente
        mostrarListaRecur(l->ptrtabla); //recursiv

    } else{

    }
}


//Eliminar Tabla

tipoRet eliminoTabla(tabla *tabl,string nombre){

    if(nombre != "") {
        //if tiene columnas pasar a eliminar las col primero
        tabla auxTable;
        tabla tablon;
        auxTable=*tabl;
        tablon=*tabl;

        if (!esVacia(tablon)){

            while(!esVacia(auxTable)) {
                if(auxTable->nombre == nombre) {
                    tablon=eliminarTabla(tablon,nombre);
                    *tabl=tablon;
                    return ok;
                }
                auxTable = auxTable->ptrtabla;
            }

            return error; // No existe la tabla :(
        }else{
            return error;
        }
    } else {
        return error;
    }

}

tabla eliminarTabla(tabla tabl, string name){
    //0 a null 1 a 0
    tabla BorrarTabl;
    tabla anterior;

    BorrarTabl = new _tabla;
    anterior = new _tabla;

    anterior=NULL;
    BorrarTabl=tabl; //apunta al inicio de la lista

    while((BorrarTabl!=NULL)&&(BorrarTabl->nombre!=name)){ //mientras que BorrarTabl no sea null y no sea igual al nombre desdeado
        anterior=BorrarTabl; //anterior se iguala a BorrarTabl

        BorrarTabl=BorrarTabl->ptrtabla; //Borrartabl va al siguiente nodo 'Tabla'
    }

    //Casos cuando salga del while
    if(BorrarTabl==NULL){  // significa que recorrio toda la lista y cuando entro al while al final BorrarTabl es igual a null/ apunta al putero sig del ultimo nodo entonces NULL
    } else if(anterior==NULL) { // Si entra aca significa que no entro al while porque el elemento que buscamos es el primero en la lista, entonces  tabl apunta al sig nodo y deleteamos el primer nodo que esta en BorrarTabl.
        tabl = tabl->ptrtabla;
        delete BorrarTabl;

    } else { // El elemento esta en la lista pero no es el primero
        anterior->ptrtabla=BorrarTabl->ptrtabla;  // hacemos que el que estaba atras apunte al mismo que estaba apuntando borrartabl 'el siguiente del actual'
        delete BorrarTabl; // borramos borrartabl

    }

    return tabl;
}

tipoRet actualizoDatos(tabla *tabl, string tablNom, string condicionCol, string condicionDato, string nuevoDatoCol, string nuevoDato) {
    tabla tablon;
    tabla auxTable;
    tablon = *tabl;
    auxTable = *tabl;

   if(tablNom == "" || condicionCol == "" || condicionCol == "") {
        return error;
    } else {
        while(!esVacia(auxTable)) {
            if(auxTable->nombre == tablNom) {
                tablon = actualizarDatos(*tabl, auxTable, condicionCol, condicionDato, nuevoDatoCol, nuevoDato);
                *tabl=tablon;
                return ok;
            }
            auxTable = auxTable->ptrtabla;
        }

        return error;
    }
}

tabla actualizarDatos(tabla tabl, tabla auxTabla, string condicionCol, string condicionDato, string nuevoDatoCol, string nuevoDato){ //update (Personas,Nombre=”Pepe”,CI,1555000);
    columna auxCol;
    fila auxFila;
    int nivel = 0;

    if(!esVacia(auxTabla->columna)) {
        auxCol = auxTabla->columna;
    } else {
        return tabl; // La tabla no tiene columnas
    }

    // Empieza a buscar fila con el dato condicion
    while(!esVacia(auxCol)) { // Recorre columnas

        if(auxCol->nombreCol == condicionCol) {

            auxFila = auxCol->fila;
            while(!esVacia(auxFila)) { // Recorre filas

                if(auxFila->dato == condicionDato) {
                    // Si encuentra dato condicion, busca columnas para actualizar datos
                    //cout << auxCol->nombreCol;
                    //cout << "ENCONTRODATO";
                    int contar = 0;
                    auxCol = auxTabla->columna;
                    auxFila = auxCol->fila;

                    while(!esVacia(auxCol)) {
                                            //cout << "NOMBRECOL " << auxCol->nombreCol << " = " << nuevoDatoCol << endl;

                       if(auxCol->nombreCol == nuevoDatoCol) {
                            //cout << "ESTAENTRANDO" << auxCol->nombreCol << endl;
                            auxFila = auxCol->fila;
                            //cout << nivel << endl;

                            // Busca filas de esa columna en el mismo nivel donde encontro los datos de la condicion
                            while(contar < nivel) {
                                auxFila = auxFila->sgtFila;
                                contar++;
                            }

                            if(contar == nivel) {
                                auxFila = auxCol->fila;

                                auxFila->dato = nuevoDato; // Reemplaza dato

                                return tabl;
                            }
                        }

                        auxCol = auxCol->sgtColumna;
                    }

                    return tabl; // No encuentra columna que cumpla con la condicion

                }

                nivel++; // Almacena el nivel de filas que va recorriendo
                auxFila = auxFila->sgtFila;
            }

            return tabl; // No encuentra dato que cumpla con la condicion
        }

        auxCol = auxCol->sgtColumna;
    }

    return tabl; // No encuentra columna que cumpla condicion*/

}

tipoRet eliminoDato(tabla *tabl,string tablNom, string colNom, string filNom){
    //condis como que si tenes una sola column pregunte si queres borrar toda la tabla antes de seguir.
    tabla tablon;
    tablon=new _tabla;
    tablon=*tabl;//tablon es modificado con la intencion de solo buscar datos

    tabla TablaBorrar;
    TablaBorrar = new _tabla;

    TablaBorrar=*tabl;
    int i;

    i=buscoDato(tablon,tablNom,colNom,filNom);//Busco la pos del dato
    if(i==-1){
        //no existe el dato
        cout << "En la fila " << colNom << " No existe ningun dato llamado " << filNom;
        //return error
    }else{
        //Func ELIMINO
        TablaBorrar=eliminarDato(TablaBorrar,i,tablNom);

        *tabl=TablaBorrar;
    }

    return ok;

}


int buscoDato(tabla tabl,string tablNom, string colNom, string filNom){ //EncontramosDato por= buscamos una tabla, una column y un dato. retorna posi de esa fila (dato)

   columna col;
   col = new _columna;

    int i=0;

    fila fil;
    fil = new _fila;

    tabla tablaAux;
    tablaAux = new _tabla;
    tablaAux=tabl;


    //Encontramos la tabla que el user nos indico
   while(tablaAux->nombre!=tablNom){
    tablaAux=tablaAux->ptrtabla;
    }

    //encontro la tabla deseada
    //arranca en esta colum de la tabla deseada
    col=tablaAux->columna;
    //Recorre columns hasta encontrar de donde el user quiere eliminar el dato
   while(col->nombreCol!=colNom){
        col=col->sgtColumna;

   }
    //Encontro la columna deseada
    fil=col->fila;

    //Recorremos filas hasta encontrar la que quiere borrar el user
    while((fil!=NULL)&&(fil->dato!=filNom)){ //Muy importante, al trabajar con el Fil cuando es nulo el while o if tiene que tener la pregunta de si es nulo como primer operador
        fil=fil->sgtFila;
        i++;
    }

    if(fil==NULL){
        i=-1;
    }
    return i;

}


tabla eliminarDato(tabla tabl, int i, string tablNom){
    columna Cols = new _columna;
    fila filita = new _fila;
    fila auxFIL = new _fila;

    tabla tablaAux = new _tabla;
    tablaAux=tabl;
    int cantFil=0;


        //Encontramos la tabla que el user nos indico
        while(tablaAux->nombre!=tablNom){
            tablaAux=tablaAux->ptrtabla;
        }

        //queremos eliminar todas las filas corresp a todas las columns de una tabla!
        Cols=tablaAux->columna; //tenemos la primera column de la tabla, TIME TO DELETE!

            while(Cols!=NULL){
                 filita=Cols->fila; //filita aca carga
                 auxFIL=NULL;
               // auxFIL=NULL;//arrancamos aux en al misma posi para tener el de atras

                while(cantFil<i){
                    auxFIL=filita;
                    filita=filita->sgtFila;
                    cantFil++;
                }

           if(i==0){ //En el caso de que la fila que queremos eliminar sea la primera o la unica

               if(filita->sgtFila==NULL){//es la unica
                    Cols->fila->sgtFila=NULL;
                    delete filita;
               }
               else{ //es la primera pero no la unica
                    Cols->fila=Cols->fila->sgtFila;
                    //cout<< Cols->fila->dato; //ACA ESTA HACIENDO EL COUT perfecto, tira el dato que tiene que tirar que seria la segunda fila ya que la idea es eliminar la primera.
                    //cout << filita->dato; //ACA hace el cout como corresponde pero cuando lo pasa en  mostrar lo deja vacios wtf
                    delete filita;
                }


            }
            else{ //En el caso de que sea cualquier otra
                auxFIL->sgtFila=filita->sgtFila;
                delete filita;

            }

                cantFil=0;
                Cols=Cols->sgtColumna;

          }

        //Ya tenemos todo en un caso ideal
    return tabl;

}


//Elimino Columna

tipoRet eliminoColumna(tabla *tabl,string tablNom, string colNom){
    if(tablNom == "", colNom == "") {
        return error; // No se especifica nombre de tabla o columna
    }

    //condis como que si tenes una sola column pregunte si queres borrar toda la tabla antes de seguir.
    tabla tablon;
    tablon=new _tabla;
    tablon=*tabl; //tablon es modificado con la intencion de solo buscar Columns

    tabla ColumnaBorrar;
    ColumnaBorrar = new _tabla;

    ColumnaBorrar=*tabl;
    int i;

    i=buscoColumna(tablon,tablNom,colNom);//Busco la pos del Columna

    if(i==-1){
    //no existe el dato
    cout << "Columna no encontrada";
    return error;

    }else if(i==-2){
    //es el primero y hay mas, entonces es el PK
    cout << "Esta deseando Eliminar la PK";
    return error;

    }else{
    //Func ELIMINO
   ColumnaBorrar=eliminarColumna(ColumnaBorrar,i,tablNom); //ColumnaBorrar es las tablas

   *tabl=ColumnaBorrar;
    }

    return ok;

}

int buscoColumna(tabla tabl,string tablNom, string colNom){ //EncontramosColumna por= buscamos una tabla, una column. retorna posi de esa column

   columna col;
   col = new _columna;

    int i=0;

    tabla tablaAux;
    tablaAux = new _tabla;
    tablaAux=tabl;


    //Encontramos la tabla que el user nos indico
   while(tablaAux->nombre!=tablNom){
    tablaAux=tablaAux->ptrtabla;
    }

    //encontro la tabla deseada
    //arranca en esta colum de la tabla deseada
    col=tablaAux->columna;
    //Recorre columns hasta encontrar de donde el user quiere eliminar el dato
   while(col->nombreCol!=colNom){
        col=col->sgtColumna;
        i++;
        if(col==NULL){
            break;
        }
   }

    if(col==NULL){ //col llego a null lo que quiere decir que no la encotro
    i=-1;
    }else if((i==0)&&(col->sgtColumna!=NULL)&&(col!=NULL)) //condicion triple, es la primer column, la siguiente existe, y la acutal no es nula(para evitar que sea i = 0 por inexistencia)
    {
    i=-2; //la column que desean borrar es pk, y hay otras no es unica

    }

    return i;

}


tabla eliminarColumna(tabla tabl, int i, string tablNom){
    columna Cols = new _columna;
    columna auxCol = new _columna;

    tabla tablaAux = new _tabla;
    tablaAux=tabl;

    int cantCol=0;


        //Encontramos la tabla que el user nos indico
        while(tablaAux->nombre!=tablNom){
            tablaAux=tablaAux->ptrtabla;
        }


        Cols=tablaAux->columna; //tenemos la primera column de la tabla, TIME TO DELETE!

            while(cantCol<i){
                auxCol=Cols;
                Cols=Cols->sgtColumna;

                cantCol++;
                }

            if (Cols->fila!=NULL){ //Llamamos a una func que borra todas las filas de la columna
            Cols->fila=vaciarFilas(Cols->fila);
            }

           if(i==0){ //En el coaso de que la columna sea la unica

                    delete Cols ;
                    Cols=NULL;
               }

          //  }
            else{ //En el caso de que sea cualquier otra

                auxCol->sgtColumna=Cols->sgtColumna;
                delete Cols;

            }

        //Ya tenemos todo en un caso ideal
    return tabl;

}


fila vaciarFilas(fila fil){

    if(fil!=NULL){

        return vaciarFilas(fil->sgtFila);

    }else{

    delete (fil);
}

    return fil;//Podria ser Return NULL tambien

}

bool verificoDuplicadoFila(tabla *tabl, string nombreTabla, string primaryKey) {
    tabla auxTabla;
    auxTabla = *tabl;

    // Recorre tablas
    while(!esVacia(auxTabla)) {

        // Existe una tabla con nombre igual a nombreTabla
        if(auxTabla->nombre == nombreTabla) {
            columna auxCol;
            auxCol = auxTabla->columna;

            // Recorre la primera columna
            if(!esVacia(auxCol)) {

                fila auxFila;
                auxFila = auxCol->fila;

                // Recorre filas
                while(!esVacia(auxFila)) {
                    if(auxFila->dato == primaryKey) {
                        return true;
                    }

                    auxFila = auxFila->sgtFila;
                }

                auxCol = auxCol->sgtColumna;
            } else {
                return false;
            }
        }

        auxTabla = auxTabla->ptrtabla;

    }
    return false;
}


int cuentoColumnas(string nombreTabla,tabla tabl){ // cuento columns en una tabla
int i=0;
tabla tablAux;
tablAux = new _tabla;
tablAux = tabl;

columna colum;
colum = new _columna;

    while(tablAux->nombre!=nombreTabla){
    tablAux= tablAux->ptrtabla;
    }
colum=tablAux->columna;

    while(colum!=NULL){
    i++;
    colum=colum->sgtColumna;
    }

return i;
}
