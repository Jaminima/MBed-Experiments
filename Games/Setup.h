#ifdef _GameOfLife
BusIn SW(BTN1_PIN, BTN2_PIN, BTN3_PIN, BTN4_PIN);

GameOfLife gameOfLife = GameOfLife();
ButtonWatch buttonwatch = ButtonWatch();

AnalogIn LDR(PC_0);
Random rnd(&LDR);

void EPressed(){
    gameOfLife.SetRandom(&rnd);
}

void buttonCheck(){
    buttonwatch.CheckAndRunEvents();
}

void gameTick(){
    gameOfLife.DoTick();
}

void display(){
    gameOfLife.Draw();
}

void Setup(){
    Scheduler _sch(3);
    _sch.tickRate_ns = 100ns;

    SW.mode(PullDown);

    buttonwatch._BoardPressed = &EPressed;

    gameOfLife.SetRandom(&rnd);

    _sch.SetSchedule_ns(0,&buttonCheck,200ns);
    _sch.SetSchedule_ms(1,&gameTick,250ms);
    _sch.SetSchedule_ns(2,&display,300ns);
    _sch.Start();

}
#endif