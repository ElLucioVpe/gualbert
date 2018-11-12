#include "header.h"

// Funciones de arboles

bool existeTabla(tabla tabl, string nombre) {

    if(esVacia(tabl)) {
        return false;
    } else {
        int compararString = nombre.compare(tabl->nombre);

        if (compararString > 0) {
            return existeTabla(tabl->ptrTablaDer, nombre);
        } else if (compararString < 0) {
            return existeTabla(tabl->ptrTablaIzq, nombre);
        } else {
            return true;
        }
    }
}

columna retornarColumna(tabla *tabl, string nombreTabla, string nombreColumna) {

    tabla tablaAux = *tabl;
    columna colAux;

    int compararString = nombreTabla.compare(tablaAux->nombre);

    if (compararString > 0) {
        colAux = retornarColumna(&tablaAux->ptrTablaDer, nombreTabla, nombreColumna);
    } else if (compararString < 0) {
        colAux = retornarColumna(&tablaAux->ptrTablaIzq, nombreTabla, nombreColumna);
    } else {
        while(!esVacia(colAux)) {

            if(colAux->nombreCol == nombreColumna) {
                return colAux;
            }

            colAux = colAux->sgtColumna;
        }

        return NULL;
    }

}

bool existeColumna(tabla *tabl, string nombreTabla, string nombreColumna) {

    tabla tablaAux = *tabl;

    int compararString = nombreTabla.compare(tablaAux->nombre);

    if (compararString > 0) {
        return existeColumna(&tablaAux->ptrTablaDer, nombreTabla, nombreColumna);
    } else if (compararString < 0) {
        return existeColumna(&tablaAux->ptrTablaIzq, nombreTabla, nombreColumna);
    } else {
        columna colAux = tablaAux->columna;

        while(!esVacia(colAux)) {

            if(colAux->nombreCol == nombreColumna) {
                return true;
            }

            colAux = colAux->sgtColumna;
        }
    }
}

tabla buscarMenor(tabla tabl) {
    if (esVacia(tabl))
       return NULL;
    while (!esVacia(HijoIzq(tabl)))
          tabl = HijoIzq(tabl);
    return tabl;
}

tabla HijoIzq(tabla tabl)
{
  return tabl->ptrTablaIzq;
}

//Inserto Tabla
tipoRet insertoTabla(tabla *tabl, string nombre){
    tabla auxTable;
    auxTable = *tabl;

    if(nombre != "") {
        while(!esVacia(auxTable)) {
            if(auxTable->nombre == nombre) {
                return error; // Ya existe una tabla con ese nombre
            }
            //auxTable = auxTable->ptrtabla;
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
   // nuevatabla->ptrtabla=NULL;

    if(esVacia(tabl)) {
        // Si es vacia la agrega  al principio
        nuevatabla->ptrTablaDer=tabl;
        tabl=nuevatabla;
    } else {
        // Recorre la lista hasta llegar a la ultima tabla
        tabla auxTable;
        auxTable = tabl;

        while(!esVacia(auxTable)) {
            if(esVacia(auxTable->ptrTablaDer)) {
              auxTable->ptrTablaDer = nuevatabla; // Asigna la tabla al final
                break;
            }
//            auxTable = auxTable->ptrtabla; // Sigue buscando
        }
    }

   return tabl;
}

//Inserto columna
tipoRet insertoColumna(tabla *tabl, string nombreTabla, string nombreColumna) {
    tabla auxTable;
    auxTable = *tabl;
    bool primaryKey = false;

    if(nombreColumna == "" || nombreTabla == "") {
        return error;
    }

    auxTable=retornarTablaBusacada(auxTable,nombreTabla);
            if(auxTable->nombre == nombreTabla) {

                columna auxCol;
                auxCol = auxTable->columna;

                // Chequea que la primera fila de la primera columna (si existe) no sea vacia
                if(!esVacia(auxCol)) {
                    fila auxFila;
                    auxFila = auxCol->fila;

                    if(!esVacia(auxCol->fila)) {
                        return error; // La tabla tiene por log menos una tupla
                    }
                } else {
                    primaryKey = true;
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
                tablon=insertarColumna(tablon, auxTable, nombreColumna, primaryKey);

                *tabl=tablon;
                return ok;

                }
        else {
        return error; // La tabla es vacia
    }
}

tabla insertarColumna(tabla tabl, tabla auxTable, string nombreColumna, bool primaryKey) {
    // Declaramos la nueva columna
    columna newCol = new _columna;
    newCol->primaryKey = primaryKey;
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

    if(existeTabla(auxTable, nombreTabla)) {

            if(std::getline(ss, token, ':')) {
                primaryKey = token;
            }

            if(!verificoDuplicadoFila(tabl, nombreTabla, primaryKey)) {

                    if(numCols==numDats){
                        tablon=insertarDato(&tablon , &auxTable, dato, nombreTabla);
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
    }
    return error; //raro este error
}

tabla insertarDato(tabla *tabl, tabla *tablaInsertarDato, string dato, string name){
    tabla tablaAux;
    tablaAux = *tablaInsertarDato;
    tabla tabRaiz = *tabl;

    if(tablaAux->nombre == name) {
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

            return tabRaiz;
        }

    } else {
        if(!esVacia(tablaAux->ptrTablaDer) && !esVacia(tablaAux->ptrTablaIzq)) {
            int compararString;
            string nombreTabla = tablaAux->nombre;
            compararString = nombreTabla.compare(name);

            // Compara nombres de tabla para saber a que hoja del arbol seguir
            if(compararString > 0 ) {
                insertarDato(&tabRaiz, &tablaAux->ptrTablaDer, dato, name);
            } else if(compararString < 0) {
                insertarDato(&tabRaiz, &tablaAux->ptrTablaIzq, dato, name);
            }
        }
    }
}

tipoRet selecto(tabla *tabl, string tabla1, string columnas, string tabla2) {
    tabla tablon = *tabl;

    if(!esVacia(tablon)) {
        if(existeTabla(tablon, tabla1)) {

            std::istringstream ss(columnas);
            std::string token;
            while(std::getline(ss, token, ':')) {
                // Puede ser que esta wea este mal
                string colNombre = token;
                if(existeColumna(&tablon, tabla1, token)) {

                } else {
                    return error;
                }
            }


        }
    }
}

tabla selecta(tabla *tabl, columna *col, string tabla2) {

}

///Inicializar tabla
void creoTabla(tabla **tabl){

    tabla nuevatabla;
    nuevatabla = new _tabla;

    nuevatabla ->ptrTablaDer =NULL; //1 -> null
    nuevatabla->ptrTablaIzq=NULL;

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
    cout << "ok" << endl;
    break;

    case 1:
    cout << "Error" << endl;
    break;

    case 2:
    cout << "No Implementado" << endl;
    break;

    }

}

bool esVacia(tabla tabl) {

    if(tabl == NULL){
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
        mostrarListaRecur(l->ptrTablaDer); //recursiv

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

            if(existeTabla(auxTable, nombre)) {
                tablon=eliminarTabla(&tablon,nombre);
                *tabl=tablon;
                return ok;
            } else {
                return error; // No existe la tabla :(
            }

        }else{
            return error;
        }
    } else {
        return error;
    }

}

tabla eliminarTabla(tabla *tabl, string name){

    tabla BorrarTabl;
    BorrarTabl = new _tabla;
    BorrarTabl = *tabl; //apunta al inicio de la lista

    if(BorrarTabl->nombre == name) {

            if(esVacia(BorrarTabl->ptrTablaIzq)) {
               BorrarTabl = BorrarTabl->ptrTablaDer;
               //delete BorrarTabl;

            }
            else if (esVacia(BorrarTabl->ptrTablaDer)) {
               BorrarTabl = BorrarTabl->ptrTablaIzq;
              // A->hijoDer = NULL;
               //delete BorrarTabl;
            } else {
                tabla guardoTabla = BorrarTabl;
                guardoTabla = buscarMenor(BorrarTabl->ptrTablaDer);
                BorrarTabl->nombre = guardoTabla->nombre;
                BorrarTabl->ptrTablaDer->ptrTablaIzq = guardoTabla->ptrTablaDer;
                //delete p;
            }

    } else {
        if(!esVacia(BorrarTabl->ptrTablaDer) && !esVacia(BorrarTabl->ptrTablaIzq)) {
            int compararString;
            string nombreTabla = BorrarTabl->nombre;
            compararString = nombreTabla.compare(name);

            // Compara nombres de tabla para saber a que hoja del arbol seguir
            if(compararString > 0 ) {
                eliminarTabla(&BorrarTabl->ptrTablaDer, name);
            } else if(compararString < 0) {
                eliminarTabla(&BorrarTabl->ptrTablaIzq, name);
            } else {
                //cout << "" << endl;
            }
        }
    }

    return *tabl;
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
            auxTable = auxTable->ptrTablaDer;
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

    return tabl; // No encuentra columna que cumpla condicion

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
    tablaAux=tablaAux->ptrTablaDer;
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
            tablaAux=tablaAux->ptrTablaDer;
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
    tablaAux=tablaAux->ptrTablaDer;
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
            tablaAux=tablaAux->ptrTablaDer;
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

        auxTabla = auxTabla->ptrTablaDer;

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
        tablAux= tablAux->ptrTablaDer;
        }
    colum=tablAux->columna;

        while(colum!=NULL){
        i++;
        colum=colum->sgtColumna;
        }

    return i;
}

tipoRet eliminoDatoTupla(tabla *tabl, string nombreTabla, string condicion) {
    tabla tabAux = *tabl;
    char comp;
    //cout << condicion.find('=') << endl;

    // Encuentra comparador
    if(condicion.find('=') != std::string::npos) {
        comp = '=';
    } else if (condicion.find('>') != std::string::npos) {
        comp = '>';
    } else if (condicion.find('<') != std::string::npos) {
        comp = '<';
    } else {
        return error;
    }

    // Encuentra comparador

    if(nombreTabla == "" || condicion == "") {
        return error; // Tabla no especificada
    } else {

        while(!esVacia(tabAux)) {

            if(tabAux->nombre == nombreTabla) {

                //Obtiene columna y datos de usuario
                string col;
                string dato;
                bool finRcorrido = false;

                std::istringstream dd(condicion);
                std::string token;

                while(std::getline(dd, token, comp)) {
                    if(finRcorrido == false) {
                        col = token;
                        finRcorrido = true;
                    } else {
                        dato = token;
                    }
                 }

                // Recorre columnas

                columna colAux;
                colAux = tabAux->columna;

                while(!esVacia(colAux)) {
                    if(colAux->nombreCol == col) {
                        //cout << comp << "KJDFJKSDFAKJDAFKJ" << endl;
                        tabla tabRes = new _tabla;
                        tabRes = eliminarDatoTupla(*tabl, tabAux, col, dato, comp);
                        *tabl = tabRes;
                        return ok;
                    }

                    colAux = colAux->sgtColumna;
                }

                return error; // Columna no existe

            }

            tabAux = tabAux->ptrTablaDer;
        }

        return error; // Tabla no existe
    }
}

tabla eliminarDatoTupla(tabla tabl, tabla tablaAux, string col, string dato, char comp) {
    columna colAux = tablaAux->columna;
    bool finRecorrido = false;

    while(!esVacia(colAux)) {
        bool elimina = false;

        // Recorre columnas
        if(colAux->nombreCol == col) {
            int level = 0;
            fila filAux = colAux->fila;

            while(!esVacia(filAux)) {
                if(colAux->fila == filAux) {
                    level = 0;
                }

                elimina = false;
                cout << "- level " << level << " dato " << filAux->dato << endl;
                if(comp == '=') {
                    if(dato.find('*') != std::string::npos) {
                        std::istringstream dd(dato);
                        std::string token;
                        string datoComparar;

                        finRecorrido = false;
                        while(std::getline(dd, token, '*')) {
                            if(finRecorrido == false) {
                                datoComparar = token;
                                finRecorrido = true;
                            }
                         }
                        //cout << "habeer " << filAux->dato << " contiene: " << dato << endl;

                         string datoCol = filAux->dato;
                         if (datoCol.find(datoComparar) != std::string::npos) {
                            //cout << "sabelo" << endl;
                            elimina = true;
                         }
                    } else if(filAux->dato == dato) {
                        //cout << "habeer " << filAux->dato << " == " << dato << endl;
                        elimina = true;
                    }
                } else if (comp == '>') {
                    int datoInt;
                    int datoFilInt;
                    std::istringstream ss(dato);
                    ss >> datoInt;

                    string datoString = filAux->dato;
                    std::istringstream ss2(datoString);
                    ss2 >> datoFilInt;

                    if(datoFilInt > datoInt) {
                        elimina = true;
                    }
                } else if (comp == '<') {
                    if(filAux->dato < dato) {
                        elimina = true;
                    }
                }

                if(elimina == true) {
                    //cout << "Va a eliminar " << filAux->dato << endl;

                    columna delCol;
                    delCol = tablaAux->columna;

                    while(!esVacia(delCol)) {

                        fila delFil;
                        delFil = delCol->fila;
                        int contar = 0;

                        while(!esVacia(delFil)) {
                            //cout << "+ level " << level << " contar " << contar << " dato " << delFil->dato << endl;

                            if(contar < level) {
                                contar++;
                            } else if (contar == level) {
                                //cout << "XDD" << endl;

                                if(!esVacia(delFil->sgtFila)){
                                    if(!esVacia(delFil->sgtFila->sgtFila) && contar > 0) {
                                        //cout << "opcion4" << endl;
                                        // OP2: si existe un dato siguiente al que se va a eliminar
                                        delFil->sgtFila = delFil->sgtFila->sgtFila;
                                        break;
                                    } else if (contar == 0) {
                                        // Si la fila esta al principio
                                        if(esVacia(delFil->sgtFila)) {
                                            // Se va a eliminar el unico item
                                            //cout << "opcion1" << endl;
                                            delCol->fila = NULL;
                                            break;
                                        } else {
                                            // Se va a eliminar el primer item
                                            //cout << "opcion2" << endl;
                                            delCol->fila = delFil->sgtFila;
                                            break;
                                        }
                                    }
                                } else if (contar == 0) {
                                    //cout << "JFJKDSK" << endl;

                                    // Si la fila esta al principio
                                    if(esVacia(delFil->sgtFila)) {
                                        // Se va a eliminar el unico item
                                        //cout << "opcion1" << endl;
                                        delCol->fila = NULL;
                                        break;
                                    } else {
                                        // Se va a eliminar el primer item
                                        //cout << "opcion2" << endl;
                                        delCol->fila = delFil->sgtFila;
                                        break;
                                    }
                                } else {
                                    // Si la fila a eliminar esta al final
                                    //cout << "opcion3 va a eliminar columna " << delFil->dato << endl;
                                    delete(delFil);
                                    break;
                                }
                                break;
                            } else {
                                cout << "Error mistico del universo tramboliko" << endl;
                            }

                            delFil = delFil->sgtFila;
                        }

                        delCol = delCol->sgtColumna;
                    }
                    //mostrarListaRet(tabl);
                }

                filAux = filAux->sgtFila;
                level++;
            }
            return tabl;

        }
        colAux = colAux->sgtColumna;
    }

}


///Una sola y ordenada no como la otra func que muestra todo
tipoRet muestroTabla(tabla l, string nomtabl){
    if(!esVacia(l)){
        mostrarTabla(l,nomtabl);
        // Finaliza
        cout << "Fin" << endl;
        return ok;
    }else{
        return error;
        cout << "Empty";
    }
}

///Mostrar y Reacomodar tabla UNA TABLA
void mostrarTabla(tabla l,string nomTabl){
    tabla tabl;
    tabl = new _tabla;
    tabl=l;

    int pos[100]; //Es para guarda posis de intercambio
    int i= 1;
    int n = 0;
    int POSIS=0;

    fila filaspk;

    columna col;
    col = new _columna;

     columna columnita;
     columnita = new _columna;

    columna col2;
    col2 = new _columna;

    columna colV; //Column Visual
    colV = new _columna;

    columna colVer;

    fila filPK;
    filPK = new _fila;
    fila filpp;
    filpp = new _fila;

    fila filver;


    fila pivot;
    string auxS;
    fila actual;

    if (!esVacia(l)){

    while((!esVacia(tabl))&&(tabl->nombre!=nomTabl)){
    tabl= tabl->ptrTablaDer;

   }

       if(tabl==NULL){
        cout << "Tabla no encontrada";

       }else{
    /// Escribe nombre de la tabla
    cout << "-----------------" << endl;
    cout << tabl->nombre << endl;

    // Chequea cada columna
        col = tabl->columna;
        colV = tabl->columna;
        colVer= tabl->columna;
        columnita = tabl->columna;

        filaspk=tabl->columna->fila;

       /// Muestra el nombre de las columnas
            while(!esVacia(colV)) {
                cout << colV->nombreCol << " : ";
                colV = colV->sgtColumna;
            }
            cout << endl;


            ///CONSIGO LAS POSIS CORRECTAS, y LAS CARGO EN UN ARRAY
                    filPK = col->fila;
                    pivot = filPK;
                    actual=NULL;
                    int compPivAct=0;

                    while (pivot!=NULL){

                    actual = columnita->fila;

                    while(actual!=NULL){

                        if ((pivot->dato).size()==(actual->dato).size()){ ///Si tiene el mismo SIZE el string
                        if( pivot->dato > actual->dato ){ ///Ahora si comparamos como es normal, para saber que pasa con el primer digito
                            i++;

                        }
                        }

                       else if ((pivot->dato).size()>(actual->dato).size()){ ///Si el string no tiene el mismo size pero el pivot es mas grande
                        i++;
                        }

                       actual=actual->sgtFila;

                    }

                    pos[n]=i;
                    i=1;
                    n++;
                    pivot=pivot->sgtFila;
                    }

                    ///SE COUTEAN RESPETANDO EL ORDEN
                    n=0;
                    int j = 1;
                    columna colChan;
                    fila filChan;
                    fila filChanAux;
                    colChan=tabl->columna;
                    filChan=colChan->fila;
                    filChanAux=colChan->fila;
                    int enc=0;

                        while(colChan!=NULL){    ///Recorremos COlumna por columna
                        filChan=colChan->fila;   ///Primer fila de la columna

                               while(filChan!=NULL){ ///Mientras la fila no sea nula

                                    if(pos[n]==j){ ///Si J corresponde con la pos significa que es la priemra voy cambiando pos hasta encontrar el que corresponde a la pos J que sera 1 2 3 4 etc

                                    cout<<filChan->dato << " : " ;
                                    n=0;
                                    j++;
                                    filChan=colChan->fila;
                                    enc=1;

                                    }

                                    if(enc==1){ ///SI lo que esta dentro de pos n es mas grande que j, se paso.. arranquemos otra vez

                                    filChan=colChan->fila;
                                    enc=0;

                                    }

                                    else{

                                    filChan=filChan->sgtFila; ///Adelanta uno
                                    n++;

                                }

                            }

                        cout << endl;
                        n=0;
                        j=1;
                        colChan=colChan->sgtColumna;
                    }
                    ///

          }

          }

          }
///ACA TERMINA

tipoRet insertoTablaAbb(tabla *tabl, string nombre){
    tabla auxTable;
    auxTable = *tabl;

    if(nombre != "") {
        while(!esVacia(auxTable)) {
            if(auxTable->nombre == nombre) {
                return error; // Ya existe una tabla con ese nombre
            }
            auxTable = auxTable->ptrTablaDer;
        }

        // Crea nueva tabla
        _tabla *tablon;
        tablon=*tabl;
        insertarAbb(tablon,nombre);
        *tabl=tablon;

        return ok;
    } else {
        return error;
    }

}



///Insertar ABB TABLA
tabla insertarAbb(_tabla *&lista, string n){
    if (lista==NULL){
        _tabla *nuevonodo = new _tabla;
        nuevonodo->nombre=n;
        lista=nuevonodo;
        lista->ptrTablaDer=NULL;
        lista->ptrTablaIzq=NULL;

    }else{
    string valorraiz=lista->nombre;
    if (n<valorraiz){
    insertarAbb(lista->ptrTablaIzq, n);
    }else
    {
    insertarAbb(lista->ptrTablaDer, n);
    }
}
//cout << lista->valor<< endl;
}


void mostrarSim(tabla lista){
    if (lista!=NULL){
            mostrarSim(lista->ptrTablaIzq);
            cout <<lista->nombre<<endl;

            mostrarSim(lista->ptrTablaDer);

    }
}

tabla retornarTablaBusacada(tabla A, string nombre){

  if (A==NULL)
    return NULL;
  else
     if (A->nombre == nombre)
        return A;
     else
        if (A->nombre < nombre)
           return retornarTablaBusacada(A->ptrTablaDer, nombre);
        else
           return retornarTablaBusacada(A->ptrTablaIzq, nombre);


}
