#include "header.h"

//Inserto Tabla
tipoRet insertoTabla(tabla *tabl, string nombre){
    tabla auxTable;
    auxTable = *tabl;

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


    if(!esVacia(auxTable)) {

        while(!esVacia(auxTable)) {
            if(auxTable->nombre == nombreTabla) {

                columna auxCol;
                auxCol = auxTable->columna;

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
    tabla tablon;
    tablon=*tabl;

    tabla auxTable;
    auxTable = *tabl;

    while(!esVacia(auxTable)){
        if(auxTable->nombre == nombreTabla) {
            tablon=insertarDato(tablon, auxTable, dato);
            *tabl=tablon;
            return ok;
        }
        auxTable = auxTable->ptrtabla;
    }
    return error;
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
    tablon=new _tabla;
    tablon=*tabl;//tablon es modificado con la intencion de solo buscar datos

    tabla TablaBorrar;
    TablaBorrar = new _tabla;

    TablaBorrar=*tabl;
    int i;

    i=buscoDato(tablon,tablNom,colNom,filNom);//Busco la pos del dato
    if(i==-1){
    //no existe el dato
    cout << "No existe ahre";
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
    while((fil->dato!=filNom)&&(fil!=NULL)){
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
        cout << "PRIMER IF";
       }
       else{ //es la primera pero no la unica
        Cols->fila=Cols->fila->sgtFila;
        //cout<< Cols->fila->dato; //ACA ESTA HACIENDO EL COUT perfecto, tira el dato que tiene que tirar que seria la segunda fila ya que la idea es eliminar la primera.
        //cout << filita->dato; //ACA hace el cout como corresponde pero cuando lo pasa en  mostrar lo deja vacios wtf
        delete filita;
        cout << "SEGUNDO ELSE";
        }


        }
        else{ //En el caso de que sea cualquier otra
        auxFIL->sgtFila=filita->sgtFila;
        delete filita;
        cout<<"ULTIMO ELSE";

           }

        cantFil=0;
        Cols=Cols->sgtColumna;

      }

    //Ya tenemos todo en un caso ideal
return tabl;

}

