# FlexiTimer Project Updates

This document tracks all significant updates and improvements to the FlexiTimer project.

---

## 2025-11-05

### F1A Configuration HTML Form - Major Updates (f1a_002.html)

#### 1. Dynamic Column Hiding for Time Settings Table
**Files Modified:** `mobile_app/bmk_flexitimer_configurator/lib/htmls/f1a_002.html`

**Feature:** Time Settings table columns now hide automatically when corresponding servo pins are set to "Not Used"

**Implementation:**
- Added CSS classes for column hiding (`.ru-column`, `.tl-column`, `.ww-column`, `.ww2-column`)
- Used `display: none` to hide columns without breaking grid layout
- Grid auto-adjusts to show only active servos: `grid-template-columns: 60px 80px repeat(N, 1fr)` where N = number of active servos
- Added column class names to all 15 timer phases × 4 servo columns (60+ HTML elements)
- JavaScript function `updateColumnVisibility()` toggles visibility based on pin selection
- Event listeners update visibility on:
  - Servo pin change
  - Page load
  - Preset load from JSON

**Benefits:**
- Cleaner UI - users only see relevant servo columns
- Data preservation - hidden column values remain in DOM
- Responsive layout - visible columns expand to fill available space

**Technical Details:**
```css
.timer-grid.hide-ru .ru-column { display: none; }
/* Grid adjusts: 4 servos → 3 servos → 2 servos → 1 servo */
```

---

#### 2. WW2 Servo Support (Second Wing Servo)
**Files Modified:** `mobile_app/bmk_flexitimer_configurator/lib/htmls/f1a_002.html`

**Feature:** Added support for F1A Flapper models with dual wing control

**Implementation:**
- Added WW2 servo pin selector in Servo Configuration section
- Added WW2 column to Time Settings table (6th column)
- Updated CSS Grid from 5 to 6 columns
- Added WW2 inputs for all 15 timer phases (pu1, pu2, cr1-3, bu1-3, fg, gl, dt, pk)
- Updated JavaScript validation and conversion functions
- Added to pin conflict detection system
- Added info system entry explaining WW2 usage

**Use Case:** F1A Flapper models use two independent wing servos for enhanced flight control and stability

**Code Changes:**
```javascript
// Servo configuration
['ru', 'tl', 'ww', 'ww2'].forEach(function(servo) {
    timer[servo] = uiValueToPwm(value, currentMode);
});
```

---

#### 3. Range Mode Selection (Servo Position Input Formats)
**Files Modified:** `mobile_app/bmk_flexitimer_configurator/lib/htmls/f1a_002.html`

**Feature:** Users can choose preferred servo position input format

**Options:**
- **0-100 (%)**: Percentage format (0% = min, 100% = max)
- **0-255**: 8-bit integer format (classic RC systems)
- **1000-2000 µs**: PWM microsecond format (default, modern servos)

**Implementation:**
- Dropdown selector in Servo Configuration section
- Real-time conversion between formats using `uiValueToPwm()` and `pwmToUiValue()`
- Dynamic header updates showing current mode
- JSON always stores PWM (1000-2000µs) regardless of UI mode
- All existing values auto-convert when mode changes
- Conversion formulas:
  ```javascript
  // 0-100 → PWM: 1000 + (value × 10)
  // 0-255 → PWM: 1000 + (value × 1000/255)
  // PWM → PWM: direct (no conversion)
  ```

**User Experience:**
- Change mode: values instantly convert
- Example: 127 (0-255) = 50% (0-100) = 1498µs (PWM)

---

#### 4. Default Values Updated to PWM Format
**Files Modified:** `mobile_app/bmk_flexitimer_configurator/lib/htmls/f1a_002.html`

**Change:** Converted all HTML default servo values from 0-255 range to 1000-2000µs PWM format

**Examples:**
- 45 → 1176µs
- 127 → 1498µs
- 255 → 2000µs

**Affected:** All 15 timer phases (on, str, cir, ola, pu1, pu2, cr1-3, bu1-3, fg, gl, dt, pk)

---

#### 5. Blur-Based Input Validation
**Files Modified:** `mobile_app/bmk_flexitimer_configurator/lib/htmls/f1a_002.html`

**Feature:** Improved servo input validation UX

**Previous Behavior:**
- Validation on every keystroke (`input` event)
- Prevented typing values outside range
- Frustrating user experience

**New Behavior:**
- Validation only when leaving input field (`blur` event)
- Users can freely type any value
- Validation happens after input is complete
- Custom modal shows error with clear explanation

**Implementation:**
```javascript
input.addEventListener('focus', function() {
    previousServoValues[this.id] = this.value; // Save old value
});

input.addEventListener('blur', function() {
    // Validate range
    if (value < limits.min || value > limits.max) {
        this.value = previousServoValues[this.id]; // Revert
        showServoRangeModal(value, rangeText, oldValue); // Show modal
    }
});
```

**Custom Modal:**
- Shows entered value
- Shows valid range
- Shows reverted value
- Orange/yellow warning theme

---

#### 6. Time Mode Selection (Interval vs Absolute)
**Files Modified:** `mobile_app/bmk_flexitimer_configurator/lib/htmls/f1a_002.html`

**Feature:** Users can view/edit timer phases in two different time formats

**Modes:**

**Interval Mode (Default):**
- Each phase shows its duration
- Example:
  - PU1: 0.03s (phase lasts 0.03s)
  - PU2: 0.10s (phase lasts 0.10s)
  - CR1: 0.63s (phase lasts 0.63s)

**Absolute Mode:**
- Each phase shows cumulative time from flight start
- Example:
  - PU1: 0.03s (starts at 0.03s)
  - PU2: 0.13s (starts at 0.13s = 0.03 + 0.10)
  - CR1: 0.76s (starts at 0.76s = 0.03 + 0.10 + 0.63)

**Implementation:**
- Dropdown selector in Servo Configuration section
- Real-time bidirectional conversion
- Snapshot-based conversion to prevent accumulation errors
- JSON always stores intervals (not absolute times)
- Auto-converts to interval before saving

**Validation:**
- In Absolute mode: each time must be ≥ previous time
- Custom modal for sequence errors
- Automatic revert to previous valid value

**Conversion Logic:**
```javascript
// Interval → Absolute
cumulativeTime = 0;
for each phase:
    cumulativeTime += intervalValue;
    display = cumulativeTime;

// Absolute → Interval
previousAbsolute = 0;
for each phase:
    intervalValue = absoluteValue - previousAbsolute;
    display = intervalValue;
    previousAbsolute = absoluteValue;
```

**Timer Phase Order:**
```javascript
['pu1', 'pu2', 'cr1', 'cr2', 'cr3', 'bu1', 'bu2', 'bu3', 'fg', 'gl']
```

**Error Handling:**
- Modal shows: previous value, entered value, reverted value
- Example: CR2 = 0.50, but CR1 = 0.53 → Error! Reverts to 0.53

---

#### 7. Enhanced Info System
**Files Modified:** `mobile_app/bmk_flexitimer_configurator/lib/htmls/f1a_002.html`

**Added Info Entries:**
- **WW2 Servo**: Explains dual wing servo for Flapper models
- **Range Mode**: Explains servo position input format options
- **Time Mode**: Explains Interval vs Absolute time display

**Format:**
```javascript
'time-mode': {
    icon: '⏱️',
    title: 'Time Mode',
    description: 'Detailed explanation with examples...'
}
```

---

### Summary Statistics

**Files Modified:** 1
- `mobile_app/bmk_flexitimer_configurator/lib/htmls/f1a_002.html`

**Lines Changed:** ~500+ lines
- CSS: ~80 lines (column hiding, responsive grid)
- HTML: ~30 lines (WW2 inputs, modals, selectors)
- JavaScript: ~400+ lines (time mode, validation, conversion)

**New Features:** 6 major features
1. Dynamic column hiding
2. WW2 servo support
3. Range Mode selection
4. Blur-based validation
5. Time Mode selection
6. Enhanced info system

**Modals Added:** 1
- Time Sequence Error Modal (for Absolute mode validation)

**Event Listeners Added:** ~20
- Time input focus/blur/change events
- Servo pin change → column visibility
- Range mode change → value conversion
- Time mode change → time format conversion

---

### Technical Highlights

**State Management:**
```javascript
window.currentServoRangeMode = 'interval' | 'absolute'
window.currentTimeMode = '0-100' | '0-255' | '1000-2000'
previousTimeValues = {}  // For time validation
previousServoValues = {} // For servo validation
```

**Grid System:**
- Dynamic column count: 2-6 columns
- Responsive with `repeat(N, 1fr)` for equal spacing
- CSS classes for each servo column

**Conversion Functions:**
- Bidirectional PWM ↔ UI format conversion
- Bidirectional Interval ↔ Absolute time conversion
- Snapshot-based to prevent accumulation errors

**Validation:**
- Pin conflict detection with revert
- Servo range validation with modal
- Time sequence validation (Absolute mode)
- All validations show custom modals with clear error messages

---

### User Experience Improvements

1. **Cleaner Interface**: Only show relevant servo columns
2. **Flexible Input**: Choose preferred servo value format
3. **Better Validation**: Errors shown after typing complete, not during
4. **Timeline Planning**: Absolute mode for flight timeline visualization
5. **Data Safety**: All validations preserve data with revert on error
6. **Responsive Layout**: Columns expand to fill space
7. **Clear Feedback**: Custom modals explain what went wrong

---

### Next Steps / Future Improvements

- [ ] Add preset export/import functionality
- [ ] Add flight simulation preview
- [ ] Add graphical servo position curves
- [ ] Add undo/redo for time edits
- [ ] Add keyboard shortcuts for mode switching
- [ ] Add CSV export for time profiles

---

**Notes:**
- All changes maintain backward compatibility with existing JSON format
- UI changes only - no firmware modifications required
- Extensive testing needed for all conversion edge cases
- Documentation updated in CLAUDE.md
