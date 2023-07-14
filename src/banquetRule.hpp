#ifndef RULE_HPP
#define RULE_HPP
#include "Calculator.hpp"
#include "functions.hpp"

// 风云宴 玉贵人2
int banquetRule9(BanquetStrictRule **, BanquetLenientRule **, States &, int);
// 风云宴 胡喜媚2
int banquetRule10(BanquetStrictRule **, BanquetLenientRule **, States &, int);

/**
 * @brief
 *
 * @param rule
 * @param s
 * @param bestfull
 * @return void
 */
void banquetRule(BanquetRule *const &rule, States &s, int *bestfull) {
    BanquetStrictRule
        *strictRule[NUM_CHEFS *
                    DISH_PER_CHEF]; // 下一阶段的规则，不受意图生效次数的影响
    BanquetLenientRule *lenientRule[NUM_CHEFS * DISH_PER_CHEF];
    for (int i = 0; i < NUM_CHEFS * DISH_PER_CHEF; i++) {
        strictRule[i] = &rule[i].strictRule;
        lenientRule[i] = &rule[i].lenientRule;
    }
    bestfull[0] = banquetRule9(strictRule, lenientRule, s, 0);
    bestfull[1] = banquetRule10(strictRule, lenientRule, s, 1);
    return;
}

// 风云宴 玉贵人2
int banquetRule9(BanquetStrictRule **strictRule,
                 BanquetLenientRule **lenientRule, States &s, int rank) {
    int d = rank * DISH_PER_CHEF * CHEFS_PER_GUEST;
    // 第1轮
    // 条件：三道蒸：下两阶段切技法料理售价+50%
    if (s.recipe[d + 0]->cookAbility.steam > 0 &&
        s.recipe[d + 1]->cookAbility.steam > 0 &&
        s.recipe[d + 2]->cookAbility.steam > 0) {
        for (int i = d + 3; i < d + 9; i++) {
            if (s.recipe[i]->cookAbility.knife > 0) {
                strictRule[i]->addRule.buff += 50;
            }
        }
    }
    // 条件：三道炸：下两阶段炒技法料理饱腹感-2
    if (s.recipe[d + 0]->cookAbility.fry > 0 &&
        s.recipe[d + 1]->cookAbility.fry > 0 &&
        s.recipe[d + 2]->cookAbility.fry > 0) {
        for (int i = d + 3; i < d + 9; i++) {
            if (s.recipe[i]->cookAbility.stirfry > 0) {
                strictRule[i]->addRule.full += -2;
            }
        }
    }
    // 条件：三道切：下两阶段煮技法料理饱腹感-2
    if (s.recipe[d + 0]->cookAbility.knife > 0 &&
        s.recipe[d + 1]->cookAbility.knife > 0 &&
        s.recipe[d + 2]->cookAbility.knife > 0) {
        for (int i = d + 3; i < d + 9; i++) {
            if (s.recipe[i]->cookAbility.boil > 0) {
                strictRule[i]->addRule.full += -2;
            }
        }
    }
    // 条件：5火：本道料理售价饱腹感-3
    for (int i = d + 0; i < d + 3; i++) {
        if (s.recipe[i]->rarity == 5) {
            lenientRule[i]->addRule.full += -3;
            break;
        }
    }
    // 第2轮
    // 条件：1火：本道料理饱腹感+5
    for (int i = d + 3; i < d + 6; i++) {
        if (s.recipe[i]->rarity == 1) {
            lenientRule[i]->addRule.full += 5;
            break;
        }
    }
    // 条件：辣：下道料理为甜时售价+100%
    for (int i = d + 3; i < d + 5; i++) {
        if (s.recipe[i]->flavor.spicy) {
            if (s.recipe[i + 1]->flavor.sweet) {
                lenientRule[i + 1]->addRule.buff += 100;
            }
            break;
        }
    }
    // 条件：鲜：下道料理为酸时售价+100%
    for (int i = d + 3; i < d + 5; i++) {
        if (s.recipe[i]->flavor.tasty) {
            if (s.recipe[i + 1]->flavor.sour) {
                lenientRule[i + 1]->addRule.buff += 100;
            }
            break;
        }
    }
    // 条件：传：本道料理基础售价+50%
    for (int i = d + 3; i < d + 6; i++) {
        if (s.chef[i / 3]->skill.ability / s.recipe[i]->cookAbility >= 5) {
            lenientRule[i]->baseRule.buff += 50;
            break;
        }
    }
    // 第3轮
    // 条件：4火：本道料理基础售价+50%
    for (int i = d + 6; i < d + 9; i++) {
        if (s.recipe[i]->rarity == 4) {
            lenientRule[i]->baseRule.buff += 50;
            break;
        }
    }
    // 条件：咸：本道料理饱腹感+3
    for (int i = d + 6; i < d + 9; i++) {
        if (s.recipe[i]->flavor.salty) {
            lenientRule[i]->addRule.full += 3;
            break;
        }
    }
    // 条件：烤：本道料理饱腹感+2
    for (int i = d + 6; i < d + 9; i++) {
        if (s.recipe[i]->cookAbility.bake > 0) {
            lenientRule[i]->addRule.full += 2;
            break;
        }
    }
    // 条件：3火：本道料理基础售价+50%
    for (int i = d + 6; i < d + 9; i++) {
        if (s.recipe[i]->rarity == 3) {
            lenientRule[i]->baseRule.buff += 50;
            break;
        }
    }
    return 13;
}

// 风云宴 胡喜媚2
int banquetRule10(BanquetStrictRule **strictRule,
                  BanquetLenientRule **lenientRule, States &s, int rank) {
    int d = rank * DISH_PER_CHEF * CHEFS_PER_GUEST;
    // 第1轮
    // 条件：三道炒：下阶段烤技法料理售价+100%
    if (s.recipe[d + 0]->cookAbility.stirfry > 0 &&
        s.recipe[d + 1]->cookAbility.stirfry > 0 &&
        s.recipe[d + 2]->cookAbility.stirfry > 0) {
        for (int i = d + 3; i < d + 6; i++) {
            if (s.recipe[i]->cookAbility.bake > 0) {
                strictRule[i]->addRule.buff += 100;
            }
        }
    }
    // 条件：传：本道料理意图生效次数加一
    for (int i = d + 0; i < d + 3; i++) {
        if (s.chef[i / 3]->skill.ability / s.recipe[i]->cookAbility >= 5) {
            lenientRule[i]->oneMore();
            break;
        }
    }
    // 条件：鲜：本道料理饱腹感+2
    for (int i = d + 0; i < d + 3; i++) {
        if (s.recipe[i]->flavor.tasty) {
            lenientRule[i]->addRule.full += 2;
            break;
        }
    }
    // 条件：蒸：本道料理售价+100%
    for (int i = d + 0; i < d + 3; i++) {
        if (s.recipe[i]->cookAbility.steam > 0) {
            lenientRule[i]->addRule.buff += 100;
            break;
        }
    }
    // 第2轮
    // 条件：酸：本道料理基础售价+50%
    for (int i = d + 3; i < d + 6; i++) {
        if (s.recipe[i]->flavor.sour) {
            lenientRule[i]->baseRule.buff += 50;
            break;
        }
    }
    // 条件：1火：本道料理基础售价+300
    for (int i = d + 3; i < d + 6; i++) {
        if (s.recipe[i]->rarity == 1) {
            lenientRule[i]->baseRule.directAdd += 300;
            break;
        }
    }
    // 条件：煮：本道料理饱腹感+2
    for (int i = d + 3; i < d + 6; i++) {
        if (s.recipe[i]->cookAbility.boil > 0) {
            lenientRule[i]->addRule.full += 2;
            break;
        }
    }
    // 条件：三道烤：下阶段炸技法料理售价+50%
    if (s.recipe[d + 3]->cookAbility.bake > 0 &&
        s.recipe[d + 4]->cookAbility.bake > 0 &&
        s.recipe[d + 5]->cookAbility.bake > 0) {
        for (int i = d + 6; i < d + 9; i++) {
            if (s.recipe[i]->cookAbility.fry > 0) {
                strictRule[i]->addRule.buff += 50;
            }
        }
    }
    // 第3轮
    // 条件：4火：本道料理售价+100%
    for (int i = d + 6; i < d + 9; i++) {
        if (s.recipe[i]->rarity == 4) {
            lenientRule[i]->addRule.buff += 100;
            break;
        }
    }
    // 条件：炒：本道料理售价-150%
    for (int i = d + 6; i < d + 9; i++) {
        if (s.recipe[i]->cookAbility.stirfry > 0) {
            lenientRule[i]->addRule.buff += -150;
            break;
        }
    }
    // 条件：神：本道料理基础售价+200
    for (int i = d + 6; i < d + 9; i++) {
        if (s.chef[i / 3]->skill.ability / s.recipe[i]->cookAbility >= 4) {
            lenientRule[i]->baseRule.directAdd += 200;
            break;
        }
    }
    // 条件：煮：本道料理售价-150%
    for (int i = d + 6; i < d + 9; i++) {
        if (s.recipe[i]->cookAbility.boil > 0) {
            lenientRule[i]->addRule.buff += -150;
            break;
        }
    }
    return 20;
}

#endif
