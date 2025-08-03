# Parry Detection System

A comprehensive parry detection system for Roblox games that can detect enemy attacks and abilities within an adjustable range.

## Features

- **Adjustable Detection Range**: Configure the detection range from 1.0 to 50.0 studs
- **Multiple Attack Types**: Detect M1 attacks, M2 attacks, abilities, and custom animations
- **Animation-Based Detection**: Uses actual game animations for accurate attack detection
- **Auto Parry**: Automatically trigger parry when attacks are detected
- **Visual Feedback**: See attack indicators and parry opportunities in real-time
- **Team Check**: Option to ignore teammates
- **Configurable Parry Window**: Adjust the timing window for successful parries
- **Animation Data Loading**: Load custom animation data from external files

## Setup

1. **Enable the System**: Go to the "Miscellaneous" tab in the menu and enable "Parry Detection"
2. **Configure Settings**: Adjust detection range, parry window, and other settings as needed
3. **Load Animation Data**: Create an `animations.txt` file with your game's animation data (see format below)

## Configuration Options

### Basic Settings
- **Enable Parry Detection**: Toggle the entire system on/off
- **Detection Range**: How far the system will detect attacks (1.0 - 50.0 studs)
- **Parry Window**: Time window for successful parries (0.1 - 1.0 seconds)

### Detection Types
- **Detect M1 Attacks**: Detect basic attacks (left-click)
- **Detect M2 Attacks**: Detect secondary attacks (right-click)
- **Detect Abilities**: Detect ability usage
- **Detect Animations**: Detect custom animations

### Auto Parry Settings
- **Auto Parry**: Automatically trigger parry when attacks are detected
- **Parry Key**: Key to press for parry (default: F)
- **Team Check**: Ignore attacks from teammates
- **Visual Feedback**: Show attack indicators on screen
- **Log Attacks**: Print attack detection to console

## Animation Data Format

The system can load animation data from an `animations.txt` file. Each line should follow this format:

```
animation_name type range duration category isAttack
```

### Parameters:
- **animation_name**: The exact name of the animation as it appears in the game
- **type**: Attack type ("M1", "M2", "Ability", "Animation")
- **range**: Attack range in studs
- **duration**: Animation duration in seconds
- **category**: Animation category ("Attack", "Ability", "Special", "Movement")
- **isAttack**: 1 for attack animations, 0 for non-attack animations

### Example:
```
SwordSlash M1 5.0 0.8 Attack 1
HeavySwing M2 8.0 1.2 Attack 1
Fireball Ability 15.0 2.0 Ability 1
DodgeRoll Animation 0.0 1.0 Movement 0
```

## How It Works

1. **Animation Detection**: The system monitors all players' animation tracks for attack animations
2. **Range Calculation**: Calculates distance between local player and attackers
3. **Timing Analysis**: Determines if attacks are within the parry window
4. **Visual Feedback**: Displays attack indicators and parry opportunities
5. **Auto Parry**: Automatically triggers parry key when conditions are met

## Visual Indicators

When visual feedback is enabled, you'll see:
- **Red circles** around detected attacks
- **Attack type labels** above each attack
- **Lines** connecting you to attacks within parry range
- **Color-coded indicators** based on your parry color settings

## Tips for Best Results

1. **Adjust Detection Range**: Set it based on your game's typical attack ranges
2. **Fine-tune Parry Window**: Start with 0.3 seconds and adjust based on game mechanics
3. **Use Animation Data**: Create a comprehensive `animations.txt` file for your specific game
4. **Enable Logging**: Use attack logging to see what animations are being detected
5. **Test Team Check**: Enable team check if your game has teams

## Troubleshooting

### No Attacks Detected
- Check if "Enable Parry Detection" is enabled
- Verify detection range is appropriate for your game
- Enable "Log Attacks" to see what's being detected
- Check if animation names in `animations.txt` match your game

### False Positives
- Adjust the parry window to be more restrictive
- Review your animation data file for incorrect attack flags
- Use team check if applicable

### Performance Issues
- Reduce detection range
- Disable visual feedback if not needed
- Close attack logging in production

## File Structure

```
├── Hacks/
│   └── parry.h              # Main parry detection system
├── animations.txt           # Animation data file (create this)
├── options.h               # Configuration options
└── main.cpp               # Main application (includes parry system)
```

## Integration

The parry system is automatically integrated into the main application. It runs in its own thread and updates the UI through the existing menu system.

## Customization

You can customize the system by:
- Modifying the `animations.txt` file for your specific game
- Adjusting detection parameters in the UI
- Changing visual feedback colors and styles
- Adding new attack types in the code

## Support

For issues or questions:
1. Check the console output for error messages
2. Verify your animation data format
3. Test with different detection ranges
4. Enable logging to debug detection issues