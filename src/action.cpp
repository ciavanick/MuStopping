#include "action.h"

MyActionInitialization::MyActionInitialization(){}

MyActionInitialization::~MyActionInitialization(){}

void MyActionInitialization::Build() const  //here we want to create the particle gun
{
    MyPrimaryGenerator *generator = new MyPrimaryGenerator();
    SetUserAction(generator);

    MyRunAction *runAction = new MyRunAction();
    SetUserAction(runAction);

    MySteppingAction *steppingAction = new MySteppingAction();
    SetUserAction(steppingAction);
} 