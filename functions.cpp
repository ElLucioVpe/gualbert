#include "header.h"

//Inserto Tabla
tipoRet insertoTabla(tabla *tabl,string nombre){
    tabla tablon;
    tablon=*tabl;
    tablon=insertarTabla(tablon,nombre);

    *tabl=tablon;
    return ok;
}

tabla insertarTabla(tabla tabl, string name){
    //0 a null 1 a 0
    tabla nuevatabla;
    nuevatabla = new _tabla;

    nuevatabla -> nombre=name;
    nuevatabla -> ptrtabla=tabl; //1 -> null
    tabl=nuevatabla; // l -->32

    return tabl;
}


//Inserto columna

tipoRet insertoColumna(tabla *tabl, string name) {
    tabla newTab;
    newTab = *tabl;

    if (!esVacia(*tabl)) {
        newTab = insertarColumna(newTab, name);
    } else {
        return error;
    }

    *tabl = newTab;
    return ok;
}

tabla insertarColumna(tabla tabl, string name) {
    columna newCol;
    newCol = new _columna;
    newCol->nombreCol = name;

    if (esVacia(tabl->columna)) {
        tabl->columna = newCol;
    } else {
        columna colAux;
        colAux = new _columna;
        colAux = tabl->columna;

        newCol->sgtColumna = colAux;
        tabl->columna = newCol;
    }

    return tabl;
}

//Inserto Dato
tipoRet insertoDato(tabla *tabl,string dato){
    tabla tablon;
    tablon=*tabl;
    if(!esVacia(tablon->columna)) {
        tablon=insertarDato(tablon,dato);
    }

    *tabl=tablon;
    return ok;
}

tabla insertarDato(tabla tabl, string dato){

    std::istringstream ss(dato);
    std::string token;

    while(std::getline(ss, token, ':')) {

        columna col;
        col = new _columna;
        col = tabl->columna;

        fila newDato;
        newDato = new _fila;
        newDato->dato = token;

        if(esVacia(col->fila)) {
            col->fila = newDato;
        } else {
            newDato->sgtFila = col->fila;
            col->fila = newDato;
        }
        //std::cout << token << '\n';
    }

    return tabl;
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
    if(aux == NULL){
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
            while(!esVacia(col)) {
                cout << col->nombreCol << " : ";
                col = col->sgtColumna;
            }
            cout << endl;

        col = l->columna;

            while(!esVacia(col)) { //columna
                fil = col->fila; //fila a la 1er fila de la col
                  while(!esVacia(fil)){ //mientras sea diferente de nulla arranca a recorrer
                    cout << fil->dato;
                    fil = fil->sgtFila;
                    cout << " : ";
                }

                col = col->sgtColumna; //paso a otra col
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

    //if tiene columnas pasar a eliminar las col primero
    tabla tablon;
    tablon=*tabl;
    if (!esVacia(tablon)){
        tablon=eliminarTabla(tablon,nombre);
        *tabl=tablon;
        return ok;
    }else{
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
        cout << "El elemento no existe";

    } else if(anterior==NULL) { // Si entra aca significa que no entro al while porque el elemento que buscamos es el primero en la lista, entonces  tabl apunta al sig nodo y deleteamos el primer nodo que esta en BorrarTabl.
        tabl = tabl->ptrtabla;
        delete BorrarTabl;

    } else { // El elemento esta en la lista pero no es el primero
        anterior->ptrtabla=BorrarTabl->ptrtabla;  // hacemos que el que estaba atras apunte al mismo que estaba apuntando borrartabl 'el siguiente del actual'
        delete BorrarTabl; // borramos borrartabl

    }

    return tabl;
}



tipoRet eliminoDato(tabla *tabl,string tablNom, string colNom, string filNom){
    //condis como que si tenes una sola column pregunte si queres borrar toda la tabla antes de seguir.
    tabla tablon;
    tablon=*tabl;

    tablon=eliminarDato(tablon,tablNom,colNom,filNom);

    *tabl=tablon;

    return ok;

}


tabla eliminarDato(tabla tabl,string tablNom, string colNom, string filNom){

   columna col,auxCOL;
   col = new _columna;
   auxCOL = new _columna;

    fila fil,auxFIL;
    fil = new _fila;
    auxFIL = new _fila;

    tabla tablaAux;
    tablaAux = new _tabla;
    tablaAux=tabl;

    //Encontramos la tabla que el user nos indico
   while(tablaAux->nombre!=tablNom){ //Basicamente en este while estoy arrastrando todos los auxiliares a la tabla correspondiente,porque tecnicamente aca son 3 listas separadas
    fil=tablaAux->columna->fila;
    col=tablaAux->columna;
    tablaAux=tablaAux->ptrtabla;

   }
    //cout << tablaAux->nombre;
    //encontro la tabla deseada
    //arranca en esta colum de la tabla deseada

    //Recorre columns hasta encontrar de donde el user quiere eliminar el dato
   while(col->nombreCol!=colNom){
        col=col->sgtColumna;

   }
    //Encontro la columna deseada
    auxFIL=fil;//arrancamos aux en al misma posi para tener el de atras

    //Recorremos filas hasta encontrar la que quiere borrar el user
    while(fil->dato!=filNom){
        auxFIL=fil;
        fil=fil->sgtFila;

    }

    //Ya tenemos todo en un caso ideal
    auxFIL->sgtFila=NULL;
    delete fil;


    return tabl;

}

