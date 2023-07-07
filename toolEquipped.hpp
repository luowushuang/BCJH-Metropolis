#ifndef TOOLEQUIPPED_HPP
#define TOOLEQUIPPED_HPP
#include "src/Chef.hpp"
#include "src/Values.hpp"

// 关于技法：
// 例：skill->ability.add(30);     // 全技法+30
// 例：skill->ability.bake += 150; // 烤技法+150,
//   bake 烤；knife 切；stirfry 炒；fry 炸；steam 蒸；boil 煮

// 关于技法售价：
// 例：skill->abilityBuff.bake += 25; // 烤售价+25%

// 关于口味售价：
// 例：skill->flavorBuff.sweet += 30; // 甜售价+30%
//   sweeet 甜；spicy 辣；salty 咸；tasty 鲜；sour 酸；bitter 苦

// 关于食材售价：
// 例：skill->materialBuff.vegetable += 15; // 蔬菜售价+15%
//   vegetable 菜类；meat 肉类；fish 鱼类；creation 面类

// 关于金币获得：
// 例：skill->coinBuff += 30; // 金币获得+30%

void toolEquipped(Chef *chef) {
    return; // 以下为示例代码，可自行修改。完成后注释此行。

    /////////// 不希望任何厨师装备厨具：

    chef->NoTool();

    /////////// 自定义厨师装备的厨具：
    auto skill = &chef->skill; // 这句不用管，放着就好。

    if (chef->name == "达浪") {              // 智能小鱼板
        skill->abilityBuff.fry += 20;        // 炸售价+20%
        skill->materialBuff.vegetable += 15; // 蔬菜售价+15%
        chef->NoTool();                      // 不允许装备其他厨具
    }
    if (chef->name == "玉涂") {    // 幸福礼花炮
        skill->ability.stirfry += 150; // 炒技法+150
        skill->abilityBuff.bake += 25; // 烤售价+25%
        chef->NoTool();                // 不允许装备其他厨具
    }
    if (chef->name == "麦格蒙") {    // 金塞醒酒壶
        skill->abilityBuff.boil += 30; // 煮售价+30%
        chef->NoTool();                // 不允许装备其他厨具
    }
    
}
#endif
