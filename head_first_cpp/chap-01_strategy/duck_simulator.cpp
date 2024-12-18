#include "duck.h"


// Cilent
int main()
{
    if (0) {
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
    }
    if (1) {
        auto mallard = MallardDuck();
        mallard.performQuack();
        mallard.performFly();
        mallard.display();
        mallard.swim();

        auto model = ModelDuck();
        model.performQuack();
        model.performFly();
        model.display();
        model.swim();
    }
    return 0;
}
