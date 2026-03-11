#ifndef IIMPRIMIBLE_H
#define IIMPRIMIBLE_H

class IImprimible {

public:

    // Metodo virtual puro
    virtual void imprimir() = 0;

    // Destructor virtual para evitar problemas de memoria
    virtual ~IImprimible() {}

};

#endif