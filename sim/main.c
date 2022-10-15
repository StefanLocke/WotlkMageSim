#include <stdio.h>
#include <time.h>
#include <stdlib.h>



struct stats
{
    float haste;
    float crit;
    float spellPower;
} ;

struct spell
{
    char* name;
    float castTime; //
    float baseDamageMin;
    float baseDamageMax;
    float scaling; //

};

struct castReport {
    float timeTook;
    float damageDone;
};


struct castReport castSpell(struct stats* playerstats, struct spell* cast) {
    
    struct castReport report;
    // damage roll

    int maxAddedDamage = cast->baseDamageMax - cast->baseDamageMin;
    float randomDamage = rand() % maxAddedDamage; 
    report.damageDone = cast->baseDamageMin + randomDamage + (playerstats->spellPower * cast->scaling);
   
    report.timeTook = cast->castTime - ((playerstats->haste/100) * cast->castTime);
    
    printf("Player cast %s for %f damage (%f) \n",cast->name,report.damageDone,report.timeTook);
    return report;
}


float sim(float time,struct stats* playerstats, struct spell* cast) {
    float currentTime = 0;
    float totalDamage = 0;
    srand(777);  
    while (currentTime < time) {
        printf("%f :: ",currentTime);
        struct castReport report = castSpell(playerstats,cast);
        currentTime = currentTime + report.timeTook;
        totalDamage = totalDamage + report.damageDone;

    }

    printf("dps was %f \n",(totalDamage/time));


    return totalDamage;
}

int main(int argc, char const *argv[])
{
    printf("Running sim\n");
    struct stats playerstats;
    playerstats.crit = 20.0;
    playerstats.haste = 20.0;
    playerstats.spellPower = 1500;

    struct spell arcaneblast;

    arcaneblast.baseDamageMin = 1185;
    arcaneblast.baseDamageMax = 1377;
    arcaneblast.name = "arcane blast";
    arcaneblast.castTime = 2.5; //seconds
    arcaneblast.scaling = 0.714; 

    sim(300,&playerstats,&arcaneblast);


    return 0;
}
