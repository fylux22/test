#pragma once

#include <unordered_set>
#include <string>

// Complete animation database extracted from the provided pastebin data
namespace AnimationDatabase {
    
    // M1 Attack Animations
    const std::unordered_set<std::string> M1_Animations = {
        // Basic Fist M1s
        "rbxassetid://15084976996", "rbxassetid://15084980343", "rbxassetid://15084992045", 
        "rbxassetid://15084993976", "rbxassetid://15144477667",
        
        // Trained Fist M1s
        "rbxassetid://16104535677", "rbxassetid://16104538511", "rbxassetid://16104540400",
        "rbxassetid://16104543160", "rbxassetid://16104545592",
        
        // Void Hands M1s
        "rbxassetid://17506776132", "rbxassetid://17506778798", "rbxassetid://17506781075",
        "rbxassetid://17506790566", "rbxassetid://17506792014",
        
        // BL M1s
        "rbxassetid://16483397075", "rbxassetid://16483341565", "rbxassetid://16483327443",
        "rbxassetid://16483422954", "rbxassetid://16483465468",
        
        // Spire M1s
        "rbxassetid://105465769634440", "rbxassetid://127798160310518", "rbxassetid://80849537186227",
        "rbxassetid://129622693779789",
        
        // Cutlass M1s
        "rbxassetid://121361663044027", "rbxassetid://94225487887674", "rbxassetid://97631998620115",
        "rbxassetid://79549636053233",
        
        // Meowmere M1s
        "rbxassetid://127516852023279", "rbxassetid://110626599133090", "rbxassetid://113511054007379",
        "rbxassetid://78968704362853"
    };
    
    // Ability/Special Attack Animations (M2, Res, Shikai, Volt moves)
    const std::unordered_set<std::string> Ability_Animations = {
        // Witch Doctor abilities
        "rbxassetid://93276102566296", "rbxassetid://94798132533627", "rbxassetid://79466780247489",
        "rbxassetid://71897740860424",
        
        // Daemon Smith abilities
        "rbxassetid://17608082660", "rbxassetid://18869643411", "rbxassetid://18740554900",
        
        // Ice Golem attacks
        "rbxassetid://96568143408107", "rbxassetid://17175893320", "rbxassetid://17165578097",
        "rbxassetid://17165878374", "rbxassetid://17175898843", "rbxassetid://18621286126",
        "rbxassetid://18621295210", "rbxassetid://18621315507", "rbxassetid://82569576200247",
        "rbxassetid://135567873205118",
        
        // Volcanic/Desert Ent abilities
        "rbxassetid://75011747185787", "rbxassetid://118522772874117", "rbxassetid://98110167320292",
        "rbxassetid://75876502277045", "rbxassetid://122447936816508", "rbxassetid://127038116435128",
        "rbxassetid://75643856752021",
        
        // Sun Guardian attacks
        "rbxassetid://95230409085456", "rbxassetid://111572288778009", "rbxassetid://71181415687372",
        "rbxassetid://135601908678046", "rbxassetid://135154953109844", "rbxassetid://124480947299494",
        "rbxassetid://114702012205126", "rbxassetid://94319685306637",
        
        // Agaricid abilities
        "rbxassetid://126784076435660", "rbxassetid://97209925955886", "rbxassetid://72292745967312",
        "rbxassetid://72434957684117", "rbxassetid://87246545963986", "rbxassetid://87320151262865",
        "rbxassetid://86095714417530", "rbxassetid://93951271277842", "rbxassetid://96555639821540",
        
        // Winged Antlion attacks
        "rbxassetid://91710897895902", "rbxassetid://99454647086558", "rbxassetid://114236004017583",
        "rbxassetid://105108662702207", "rbxassetid://99509694888316",
        
        // Harpy abilities
        "rbxassetid://18543070463", "rbxassetid://18543074006", "rbxassetid://18543077536",
        
        // Hellbat attacks
        "rbxassetid://18483411505", "rbxassetid://18483465219", "rbxassetid://18497500757",
        
        // Lurker attacks
        "rbxassetid://18485473050", "rbxassetid://18486340358", "rbxassetid://18486548498",
        "rbxassetid://130981033686781", "rbxassetid://17891975381", "rbxassetid://120185546765112",
        "rbxassetid://120700479735412", "rbxassetid://130574724684615", "rbxassetid://81922712473326",
        "rbxassetid://78142851512461",
        
        // Cacto abilities
        "rbxassetid://17015134465", "rbxassetid://17015027213", "rbxassetid://17015083245",
        "rbxassetid://17016128979", "rbxassetid://18822790470", "rbxassetid://127096173266284",
        "rbxassetid://136042149854500",
        
        // Yeti attacks
        "rbxassetid://122310895039286", "rbxassetid://104670536496397", "rbxassetid://112073744944483",
        
        // Various monster attacks
        "rbxassetid://129065041585669", "rbxassetid://107656767187535", "rbxassetid://115167687493349",
        "rbxassetid://111037092611514", "rbxassetid://83641751981908", "rbxassetid://97658129879185",
        "rbxassetid://98653740554466", "rbxassetid://102166337173259", "rbxassetid://88026955646274",
        "rbxassetid://114668625400138"
    };
    
    // Defensive/Parry animations (to avoid false positives)
    const std::unordered_set<std::string> Defensive_Animations = {
        "rbxassetid://94319685306637", // Sun Guardian Block
        "rbxassetid://122447936816508", // Volcanic Ent Block
        "rbxassetid://15309667947", // General knocked/defensive animations
        "rbxassetid://15311261198"
    };
    
    // Check if animation ID represents an attack
    inline bool IsAttackAnimation(const std::string& animationId) {
        return M1_Animations.count(animationId) || Ability_Animations.count(animationId);
    }
    
    // Check if animation ID represents a defensive move
    inline bool IsDefensiveAnimation(const std::string& animationId) {
        return Defensive_Animations.count(animationId);
    }
    
    // Check if it's specifically an M1 attack
    inline bool IsM1Attack(const std::string& animationId) {
        return M1_Animations.count(animationId);
    }
    
    // Check if it's an ability/special attack
    inline bool IsAbilityAttack(const std::string& animationId) {
        return Ability_Animations.count(animationId);
    }
}