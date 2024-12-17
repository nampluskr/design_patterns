#include "fly_behavoir.h"
#include "quack_behavoir.h"
#include "duck.h"


// Cilent
int main()
{
    Duck* mallard = new MallardDuck();

    mallard->performQuack();
    mallard->performFly();
    mallard->display();
    mallard->swim();

    Duck* model = new ModelDuck();

    model->performQuack();
    model->performFly();
    model->display();
    model->swim();

    delete mallard;
    delete model;
    return 0;
}
