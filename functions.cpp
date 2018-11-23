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

        return retornarColumna(&tablaAux->ptrTablaDer, nombreTabla, nombreColumna);
    } else if (compararString < 0) {

        return retornarColumna(&tablaAux->ptrTablaIzq, nombreTabla, nombreColumna);
    } else {
        if (esVacia(tablaAux->columna)) {
            return NULL;
        } else {
            colAux = tablaAux->columna;
        }

        while(!esVacia(colAux)) {

            if(colAux->nombreCol == nombreColumna) {
                return colAux;
            }

            colAux = colAux->sgtColumna;
        }
    }

    return NULL;

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

tabla HijoIzq(tabla tabl) {
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
                fila auxFila;

                // Chequea que la primera fila de la primera columna (si existe) no sea vacia
                if(!esVacia(auxCol)) {
                    auxFila = auxCol->fila;

                    if(!esVacia(auxCol->fila)) {
                        cout << "es este el error kbeza2" << endl;
                        //return error; // La tabla tiene por log menos una tupla
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

///Inserto Dato
tipoRet insertoDato(tabla *tabl, string nombreTabla, string dato){

    tabla tablon;
    tablon=*tabl;

    int numDats=0;
    int numCols=0;

    tabla auxTable;
    auxTable = *tabl;
    tabla enviarTabla;

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

            enviarTabla = retornarTablaBusacada(auxTable, nombreTabla);

            if(std::getline(ss, token, ':')) {
                primaryKey = token;
            }

            if(!verificoDuplicadoFila(tabl, nombreTabla, primaryKey)) {
                    if(numCols==numDats){
                        tablon=insertarDato(&tablon , &enviarTabla, dato, nombreTabla);
                       *tabl=tablon;
                       return ok;
                    } else {
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

tabla insertarDato(tabla *tabl, tabla *tablaInsertarDato, string dato, string name) {

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

    }
}
///Proyecto Tabla
tipoRet proyectoTabla(tabla *tabl, string tabla1, string columnas, string tabla2) {
    tabla tablon = *tabl;

    if(!esVacia(tablon)) {
        if(existeTabla(tablon, tabla1)) {

            std::istringstream ss(columnas);
            std::string token;

            // Verifica que las tablas dadas por el usuario existan en tabla1
            while(std::getline(ss, token, ':')) {
                // Puede ser que esta wea este mal

                string colNombre = token;
                if(!existeColumna(&tablon, tabla1, token)) {
                    cout <<  "V1 -- No existe columna: " <<token << endl;
                    return error;
                }
            }

            muestroR(insertoTablaAbb(tablon, tabla2));

            std::istringstream ssx(columnas);
            std::string token2;

            while(std::getline(ssx, token2, ':')) {

                cout <<  "V2 -- Nombre columna: " << token2 << " NomTab: " << tabla1 << endl;

                // Envia columna con datos
                columna colAux = retornarColumna(tabl, tabla1, token2);

                // Proyecta la tabla con la columna de datos dados
                tablon = proyectarTabla(&tablon, colAux, tabla2);
                *tabl=tablon;

            }

            return ok;
        }
    }

    return error;
}
///Proyectar Tabla
tabla proyectarTabla(tabla *tabl, columna col, string tabla2) {

    // Tabla raiz
    tabla tablon = *tabl;

    // Columna con datos
    columna auxCol = col;

    // Columna a proyectar
    columna nuevaCol;

    // Fila a ingresar datos
    fila nuevaFil;

    // Insertamos columna en tabla nueva
    muestroR(insertoColumna(&tablon, tabla2, auxCol->nombreCol));

    tabla auxTabla = retornarTablaBusacada(tablon, tabla2);
    nuevaCol = retornarColumna(&tablon, tabla2, auxCol->nombreCol);

    fila auxFil = col->fila;
    bool esPrimera = true;

    while(!esVacia(auxFil)) {
        fila nuevoDato = new _fila;

        if(esPrimera) {
            fila newFila = new _fila;
            newFila->dato = auxFil->dato;
            nuevaCol->fila = newFila;
            nuevaFil = nuevaCol->fila;
            esPrimera = false;

        } else {
            nuevoDato->dato = auxFil->dato;
            nuevoDato->sgtFila = NULL;

            nuevaFil->sgtFila = nuevoDato;
            nuevaFil = nuevaFil->sgtFila;
        }
        auxFil = auxFil->sgtFila;
    }

    return tablon;
}

///Inicializar tabla
void creoTabla(tabla **tabl){

    tabla nuevatabla;
    nuevatabla = new _tabla;
    nuevatabla=NULL;

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
        mostrarListaRecur(l->ptrTablaDer);
        mostrarListaRecur(l->ptrTablaIzq);
        //recursiv

    } else{

    }
}

///Eliminar Tabla Gualbert
void eliminoTablaAbb(tabla &A, string valor)
{
    if (A==NULL)
    {
        cout << "El árbol está vacio";
    }
    if (A->nombre > valor)
    {
       eliminoTablaAbb(A->ptrTablaIzq, valor);
    }
    else
    {
        if (A->nombre < valor)
        {
           eliminoTablaAbb(A->ptrTablaDer, valor);
        }
        else
        {
            tabla ptrElimino;
            tabla p;
            ptrElimino = A; //guardo el nodo  encontrado a eliminar

            if (A->ptrTablaIzq==NULL)
            {
               A = A->ptrTablaDer;
               //A->hijoIzq = NULL;
               delete ptrElimino;

            }
            else
            {
                if (A->ptrTablaDer==NULL)
                {
                   A = A->ptrTablaIzq;
                  // A->hijoDer = NULL;
                   delete ptrElimino;
                }
                else
                {
                    p = buscarMenor(A->ptrTablaDer);
                    A->nombre = p->nombre;
                    A->ptrTablaDer->ptrTablaIzq = p->ptrTablaDer;
                    delete p;
                }
            }
        }
    }
  return;

}



//Eliminar Tabla

tipoRet eliminoTabla(tabla *tabl, string nombre){

    if(nombre != "") {
        //if tiene columnas pasar a eliminar las col primero
        tabla auxTable;
        tabla tablon;
        tablon=*tabl;

        if (!esVacia(tablon)){

            if(existeTabla(tablon, nombre)) {
                eliminoTablaAbb(*tabl, nombre);
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

tabla eliminarTabla(tabla *tabl, tabla *aux, string name){

    tabla BorrarTabl;
    BorrarTabl = new _tabla;
    tabla auxTable = *tabl;
    BorrarTabl = *aux; //apunta al inicio de la lista

    cout << "buscando: " << BorrarTabl->nombre << endl;

    if(BorrarTabl->nombre == name) {

            if(esVacia(BorrarTabl->ptrTablaDer) && esVacia(BorrarTabl->ptrTablaIzq)) {
                cout << "hmm1: " << endl;

                delete(BorrarTabl);
                return auxTable;

            } else if (esVacia(BorrarTabl->ptrTablaDer)) {
                cout << "hmm2: " << endl;

               BorrarTabl = BorrarTabl->ptrTablaIzq;
               return auxTable;

            } else if (esVacia(BorrarTabl->ptrTablaIzq)) {
                cout << "hmm3: " << BorrarTabl->ptrTablaDer->nombre <<  endl;

                cout << "antes: " << BorrarTabl->nombre <<  endl;
               tabla tabRep = BorrarTabl->ptrTablaDer;
               BorrarTabl = tabRep;
               cout << "despues: " << BorrarTabl->nombre <<  endl;

               return auxTable;

            } else {

                tabla guardoTabla = BorrarTabl;
                guardoTabla = buscarMenor(BorrarTabl->ptrTablaDer);
                BorrarTabl->nombre = guardoTabla->nombre;
                BorrarTabl->ptrTablaDer->ptrTablaIzq = guardoTabla->ptrTablaDer;
            }

    } else {

            int compararString;
            string nombreTabla = BorrarTabl->nombre;
            compararString = nombreTabla.compare(name);

            // Compara nombres de tabla para saber a que hoja del arbol seguir
            if(compararString > 0 ) {
                return eliminarTabla(&auxTable, &BorrarTabl->ptrTablaIzq, name);
            } else if(compararString < 0) {
                return eliminarTabla(&auxTable, &BorrarTabl->ptrTablaDer, name);
            }

    }
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
           ///Fixear aca
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

tipoRet unirTablas(tabla *tabl, string nombreTabla1, string nombreTabla2, string nombreTabla3) {
    tabla tablon = *tabl;
    tabla tabla1;
    tabla tabla2;

    tabla1 = retornarTablaBusacada(tablon, nombreTabla1);
    tabla2 = retornarTablaBusacada(tablon, nombreTabla2);

    if (esVacia(tabla1) || esVacia(tabla2)) {
        return error; // Al menos una de las tablas es vacia
    } else {
        if(tabla1->columna->nombreCol != tabla2->columna->nombreCol) {
            return error; // Las columnas son distintas

        } else {

            columna colTab1 = tabla1->columna;
            columna colTab2 = tabla2->columna;

            if(esVacia(colTab1->fila) || esVacia(colTab2->fila)) {
                return error; // No tienen tuplas en la primer columna

            } else {

                while(!esVacia(colTab1)) {

                    while(!esVacia(colTab2) && colTab2->primaryKey == 0) {

                        if(colTab1->nombreCol == colTab2->nombreCol) {
                            return error;

                        }

                        colTab2 = colTab2->sgtColumna;
                    }
                    colTab1 = colTab1->sgtColumna;
                }

                tabla tablaRaiz = unoTablas(&tablon, tabla1, tabla2, nombreTabla3);
                *tabl = tablaRaiz;
                return ok;

            }
        }
    }
}

tabla unoTablas(tabla *tabl, tabla tabla1, tabla tabla2, string nombreTabla3) {
    tabla tablon = *tabl;
    insertoTablaAbb(tablon, nombreTabla3);
    tabla tabla3 = retornarTablaBusacada(tablon, nombreTabla3);
    bool primerDato = true;

    columna colTab1 = tabla1->columna;
    columna colTab2 = tabla2->columna;

    // Crea nuevas columnas y le asigna filas

    while(colTab1) {
        fila newFila = new _fila;
        insertoColumna(&tablon, nombreTabla3, colTab1->nombreCol);
        columna newCol = retornarColumna(&tablon, nombreTabla3, colTab1->nombreCol);
        newCol->fila = newFila;
        colTab1 = colTab1->sgtColumna;
    }

    while(colTab2) {
        fila newFila = new _fila;
        insertoColumna(&tablon, nombreTabla3, colTab2->nombreCol);
        columna newCol = retornarColumna(&tablon, nombreTabla3, colTab2->nombreCol);
        newCol->fila = newFila;
        colTab2 = colTab2->sgtColumna;
    }

    // Retorna valores de tabla3
    columna colTab3 = tabla3->columna;

    colTab1 = tabla1->columna;
    colTab2 = tabla2->columna;

    bool agregarDato = false;
    int levelTab1 = 0;
    int levelTab2 = 0;

    if(!esVacia(colTab1)) {

        if(!esVacia(colTab2)) {

            fila filTab1 = colTab1->fila;
            fila filTab2 = colTab2->fila;

            while(!esVacia(filTab1)) {
                levelTab2 = 0;

                while(!esVacia(filTab2)) {

                    if(filTab1->dato == filTab2->dato) {
                        agregarDato = true;
                    }

                    cout << "dato1: " << filTab1->dato << " dato2: " << filTab2->dato << endl;


                    if(agregarDato) {
                        // adasdas
                        cout << "dato1: " << filTab1->dato << " dato2: " << filTab2->dato << endl;

                        columna newColTab1 = tabla1->columna;
                        columna newColTab2 = tabla2->columna;
                        columna auxTab3 = colTab3;
                        string primaryKey = "";
                        bool esPK = true;

                        // Recorre tabla 1 hasta llegar a levelTab1
                        while(!esVacia(newColTab1)) {
                            fila auxFil3 = auxTab3->fila;

                            cout << "columna: " << auxTab3->nombreCol << endl;

                            fila newFilTab1 = newColTab1->fila;

                            int contar = 0;
                            while(contar < levelTab1) {
                                newFilTab1 = newFilTab1->sgtFila;
                            }

                            if(esPK == true) {
                                primaryKey = newFilTab1->dato;
                                esPK = false;
                            }

                            cout << "dato1: " << newFilTab1->dato << endl;

                            if(primerDato) {
                                auxFil3->dato = newFilTab1->dato;
                            } else {
                                fila newFila = new _fila;
                                newFila->dato = newFilTab1->dato;
                                auxFil3->sgtFila = newFila;
                            }

                            newColTab1 = newColTab1->sgtColumna;
                            auxTab3 = auxTab3->sgtColumna;
                        }

                        // Recorre tabla 2 hasta llegar a levelTab2
                        while(!esVacia(newColTab2)) {
                            fila auxFil3 = auxTab3->fila;

                            cout << "columna: " << auxTab3->nombreCol << endl;

                            fila newFilTab2 = newColTab2->fila;

                            int contar = 0;
                            while(contar < levelTab1) {
                                newFilTab2 = newFilTab2->sgtFila;
                            }

                                                            cout << "dato2: " << newFilTab2->dato << endl;


                            if(newFilTab2->dato != primaryKey) {
                                if(primerDato) {
                                    auxFil3->dato = newFilTab2->dato;
                                    auxFil3 = auxFil3->sgtFila;
                                } else {
                                    fila newFila = new _fila;
                                    newFila->dato = newFilTab2->dato;
                                    auxFil3->sgtFila = newFila;
                                    auxFil3 = auxFil3->sgtFila;

                                }

                                auxTab3 = auxTab3->sgtColumna;
                            }

                            newColTab2 = newColTab2->sgtColumna;
                        }
                     }

                     agregarDato = false;
                     primerDato = false;

                    levelTab2++;
                    filTab2 = filTab2->sgtFila;
                }

                levelTab1++;
                filTab1 = filTab1->sgtFila;
            }

            colTab2 = colTab2->sgtColumna;
        }

        colTab1 = colTab1->sgtColumna;
    }

    return tablon;
}

tipoRet proyectarWhere(tabla *tabl, string nombreTabla1, string condicion, string nombreTabla2) {
    tabla tablon = new _tabla;
    tabla auxTable = new _tabla;
    tablon = *tabl;
    auxTable = *tabl;

   if(nombreTabla1 == "" || condicion == "" || nombreTabla2 == "") {
        return error;
    } else {
        auxTable = retornarTablaBusacada(tablon, nombreTabla1);

        if(!esVacia(auxTable)) {
            tablon = proyectoWhere(*tabl, auxTable, nombreTabla1, condicion, nombreTabla2);
            auxTable=tablon;
            return ok;
        } else {
            return error;
        }
    }
}

tabla proyectoWhere(tabla tabl, tabla auxTabla, string nombreTabla1, string condicion, string nombreTabla2) {

    columna auxCol;
    fila auxFila;
    int nivel = 0;
    bool primerDato = true; // Cuenta cuantos datos han sido agregados
    char comp;
    bool agregarDato = false;
    string datoColumna = "";
    string datoComp = "";

    if(!esVacia(auxTabla->columna)) {
        auxCol = auxTabla->columna;
    } else {
        return tabl;
    }

    // Encuentra comparador
    if(condicion.find('=') != std::string::npos) {
        comp = '=';
    } else if (condicion.find('>') != std::string::npos) {
        comp = '>';
    } else if (condicion.find('<') != std::string::npos) {
        comp = '<';
    } else {
        return tabl;
    }

    // Separa datos provisionados por el usuario
    std::istringstream ss(condicion);
    std::string token;

    bool primeraVez = true;
    while(std::getline(ss, token, comp)) {
        if (primeraVez) {
            datoColumna = token;
            primeraVez = false;
        } else {
            datoComp = token;
        }

    }

    // Declaraciones para tabla ya existente
    columna colComp = retornarColumna(&tabl, nombreTabla1, datoColumna);

    // Declaraciones para tabla nueva
    insertoTablaAbb(tabl, nombreTabla2);
    tabla tablaNueva = retornarTablaBusacada(tabl, nombreTabla2);

    // Recorre todas las columnas
    if(!esVacia(colComp)) {

        fila filComp = colComp->fila;
        nivel = 0;

        while(!esVacia(colComp)) {
            // Crea nueva columna en tabla2
            insertoColumna(&tabl, nombreTabla2, colComp->nombreCol);
            colComp = colComp->sgtColumna;
        }

        // Recorre cada fila de las columnas
        while(!esVacia(filComp)) {
            agregarDato = false;
            //cout << " UF COMO PEGAN ESAS TUCS dato " << filComp->dato << comp << endl;

            fila filaInsertar;

            // Compara datos
            if(comp == '=') {
                if(filComp->dato == datoComp) {
                    agregarDato = true;
                }
            } else if (comp == '>') {
                if(filComp->dato > datoComp) {
                    agregarDato = true;
                }
            } else if (comp == '<') {
                if(filComp->dato < datoComp) {
                    agregarDato = true;
                }
            } else {
                agregarDato = false;
            }

            // Si los datos concuerdan, ingresa los datos a la nueva tabla
            if(agregarDato) {

                columna auxCol = auxTabla->columna;
                while(!esVacia(auxCol)) {

                    columna nuevaColumna = retornarColumna(&tabl, nombreTabla2, auxCol->nombreCol);
                    filaInsertar = nuevaColumna->fila;

                    // Recorre los datos
                    int contar = 0;

                    fila auxFil = auxCol->fila;
                    while(!esVacia(auxFil)) {
                        //cout << "contando " << contar << " nivel " << nivel <<  " dato " << auxFil->dato << endl;

                        if(contar == nivel) {
                            break;
                        } else {
                            contar++;
                            auxFil = auxFil->sgtFila;
                        }
                    }

                    cout << "contar" << contar << " level" << nivel << " dato " << auxFil->dato << endl;

                    if(nivel == contar) {
                        fila filNueva = new _fila;
                        filNueva->dato = auxFil->dato;
                        filNueva->sgtFila = NULL;

                        if(primerDato) {
                            nuevaColumna->fila = filNueva;
                            filaInsertar = nuevaColumna->fila;
                            //cout << "primerDato " << filNueva->dato << " true" << endl;
                        } else {

                            while(!esVacia(filaInsertar->sgtFila)) {
                                filaInsertar = filaInsertar->sgtFila;
                            }

                            filaInsertar->sgtFila = filNueva;
                            filaInsertar = filaInsertar->sgtFila;
                        }
                    }

                    auxCol = auxCol->sgtColumna;
                }

                primerDato = false;
            }

            nivel++; // Agrega un nuevo nivel
            filComp = filComp->sgtFila;

        }

        //colComp = colComp->sgtColumna;
    }

    cout << "proceso finalizado" << endl;

    return tabl;
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

    tabla tablaEncontrar;
    tablaEncontrar=*tabl;

    if(!existeTabla(tablaEncontrar,tablNom)){
    cout << "No existe esa tabla";
    return error;

    }
    if(!existeColumna(&tablaEncontrar,tablNom,colNom)){
    cout << "No existe esa columna";
    return error;
    }


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
    tablaAux=retornarTablaBusacada(tablaAux,tablNom);

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
            tablaAux=retornarTablaBusacada(tablaAux,tablNom);

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
    tablaAux=retornarTablaBusacada(tablaAux,tablNom);
    if(tablaAux!=NULL){

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
}


tabla eliminarColumna(tabla tabl, int i, string tablNom){
    columna Cols = new _columna;
    columna auxCol = new _columna;

    tabla tablaAux = new _tabla;
    tablaAux=tabl;

    int cantCol=0;


        //Encontramos la tabla que el user nos indico
        tablaAux=retornarTablaBusacada(tablaAux,tablNom);


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
    // Recorre tablas
    auxTabla = retornarTablaBusacada(*tabl, nombreTabla);

    if(!esVacia(auxTabla)) {
            // Existe una tabla con nombre igual a nombreTabla
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

    } else {
        return false;
    }

}


int cuentoColumnas(string nombreTabla,tabla tabl){ // cuento columns en una tabla
    int i=0;
    tabla tablAux;
    tablAux = new _tabla;
    tablAux = tabl;

    columna colum;
    colum = new _columna;

    tablAux = retornarTablaBusacada(tabl, nombreTabla);
    colum = tablAux->columna;

    while(!esVacia(colum)){
        i++;
        colum = colum->sgtColumna;
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

        //while(!esVacia(tabAux)) {

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

            ///Fixeando ACA
            //tabAux = tabAux->ptrTablaDer;
            //tipoRet eliminoDatoTupla(tabAux->ptrTablaDer,nombreTabla,condicion);
            //tipoRet eliminoDatoTupla(tabAux->ptrTablaIzq,nombreTabla,condicion);
      //  }

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

        tabl=retornarTablaBusacada(tabl,nomTabl);

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
///ACA TERMINA

///InsertoABB
tipoRet insertoTablaAbb(tabla &tabl, string nombre){

    if(nombre != "") {
        // Crea nueva tabla
        insertaNodoArbol(tabl,nombre);

        return ok;
    } else {
        return error;
    }

}

///Insertar ABB TABLA
void insertaNodoArbol( tabla &A, string valor )
{

  if (A==NULL) {
      A = new  _tabla; // creo el nuevo espacio de memoria
      A->nombre = valor; // asigno el valor al nodo
      A->ptrTablaDer = NULL; // pongo puntero izq en null
      A->ptrTablaDer = NULL; // pongo puntero der en null
   }
   else
   {
      if (valor < A->nombre ) { //pregunto si es menor para ir por la izquierda
         insertaNodoArbol(A->ptrTablaIzq, valor ); // vuelvo a llamar a insertar nodo por la izq.
      }
      else
      {
           if ( valor > A->nombre ) { // pregunto si es mayor para ir por la derecha
               insertaNodoArbol(A->ptrTablaDer, valor ); // vuelvo a llamar a insertar nodo por la der
            }
            else
            {
                   cout <<  "Valor ya existe" ; // valor ya existe.
                   cin.get();
            }
      }
   }
}


void mostrarSim(tabla lista){
    if (lista!=NULL){
            mostrarSim(lista->ptrTablaIzq);
            cout <<lista->nombre;

            while(lista->columna!=NULL){
            cout << endl;
            cout <<lista->columna->nombreCol;

                    while(lista->columna->fila!=NULL){
                        cout <<lista->columna->fila->dato<< endl;
                        lista->columna->fila=lista->columna->fila->sgtFila;
                    }

            lista->columna=lista->columna->sgtColumna;
            }
            cout << endl;
            cout << endl;
            mostrarSim(lista->ptrTablaDer);

    }
}

void printTables(tabla lista){
    if (lista!=NULL){
            printTables(lista->ptrTablaIzq);
            cout <<lista->nombre;
            cout << endl;
            cout << endl;
            printTables(lista->ptrTablaDer);
    }
}

void printMetadata(tabla lista){
    if (lista!=NULL){
            printMetadata(lista->ptrTablaIzq);
            cout <<lista->nombre;

            while(lista->columna!=NULL){
            cout << endl;
            cout <<lista->columna->nombreCol;
            lista->columna=lista->columna->sgtColumna;
            }
            cout << endl;
            cout << endl;
            printMetadata(lista->ptrTablaDer);

    }
}

tipoRet printoMetadata(tabla lista){
if(lista!=NULL){
    printMetadata(lista);
    return ok;
}else{
    return error;
}

}

tipoRet printoTables(tabla lista){
if(lista!=NULL){
    printTables(lista);
    return ok;
}else{
    return error;
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
