<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Model Airplane Timer Configuration</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
    <style>
        /* Mobile-first styling */
        body {
            background-color: #000; /* High contrast black background */
            color: #fff; /* High contrast white text */
            font-family: Arial, sans-serif;
            margin: 0;
            padding: 10px;
        }

        h1 {
            color: #FFD700; /* Gold color for headers */
            text-align: center;
            font-size: 24px;
            margin-bottom: 20px;
        }

        .section {
            margin-bottom: 20px;
            padding: 15px;
            border: 2px solid #fff;
            border-radius: 10px;
        }

        .section h2 {
            color: #FFD700;
            margin-bottom: 15px;
            font-size: 20px;
            text-align: center;
        }

        label {
            display: block;
            font-size: 16px;
            margin-bottom: 5px;
        }

        input[type="text"],
        input[type="number"],
        select {
            width: 100%;
            padding: 10px;
            font-size: 16px;
            margin-bottom: 15px;
            border: none;
            border-radius: 5px;
            background-color: #333;
            color: #fff;
            box-sizing: border-box;
        }

        input[type="checkbox"] {
            width: 20px;
            height: 20px;
            vertical-align: middle;
            margin-right: 10px;
        }

        .checkbox-label {
            display: flex;
            align-items: center;
            font-size: 16px;
            margin-bottom: 15px;
        }

        .preset-buttons {
            display: flex;
            justify-content: space-between;
        }

        .preset-buttons button {
            width: 23%;
            padding: 10px;
            font-size: 16px;
            background-color: #444;
            color: #fff;
            border: none;
            border-radius: 5px;
        }

        .timer-row {
            display: flex;
            flex-wrap: wrap;
            justify-content: space-between;
            margin-bottom: 15px;
        }

        .timer-row > div {
            flex: 0 0 48%;
        }

        .timer-row > div label {
            margin-bottom: 5px;
        }

        .timer-row > div input {
            width: 100%;
        }

        input[type="submit"] {
            background-color: #FFD700;
            color: #000;
            font-size: 18px;
            padding: 10px;
            border: none;
            border-radius: 5px;
            width: 100%;
            cursor: pointer;
        }

        /* Color-blind friendly styling */
        /* Avoid problematic color combinations */
    </style>
</head>
<body>

    <h1>Timer Configuration</h1>

    <form onsubmit="submitForm(event)">
        <!-- Preset Timer Modes -->
        <div class="section">
            <h2>Preset Timer Modes</h2>
            <div class="preset-buttons">
                <button type="button">Preset 1</button>
                <button type="button">Preset 2</button>
                <button type="button">Preset 3</button>
                <button type="button">Preset 4</button>
            </div>
        </div>

        <!-- Model Identification -->
        <div class="section">
            <h2>Model Identification</h2>
            <label for="class">Class:</label>
            <input type="text" id="class" name="class" placeholder="e.g., F1A">

            <label for="model-name">Name:</label>
            <input type="text" id="model-name" name="model-name" placeholder="e.g., MyModel">
        </div>

        <!-- Servo Configuration -->
        <div class="section">
            <h2>Servo Configuration</h2>
            <label for="servo-pin">Servo Pin (1-6):</label>
            <select id="servo-pin" name="servo-pin">
                <option value="1">1</option>
                <option value="2">2</option>
                <option value="3">3</option>
                <option value="4">4</option>
                <option value="5">5</option>
                <option value="6">6</option>
            </select>

            <label for="start-position">Start Position (0-180 degrees):</label>
            <input type="number" id="start-position" name="start-position" min="0" max="180" value="90">

            <label for="direction">Direction:</label>
            <select id="direction" name="direction">
                <option value="CW">Clockwise</option>
                <option value="CCW">Counter-Clockwise</option>
            </select>
        </div>

        <!-- Start Button Configuration -->
        <div class="section">
            <h2>Start Button Configuration</h2>
            <label for="start-button-pin">Start Button Pin (1-6):</label>
            <select id="start-button-pin" name="start-button-pin">
                <option value="1">1</option>
                <option value="2">2</option>
                <option value="3">3</option>
                <option value="4">4</option>
                <option value="5">5</option>
                <option value="6">6</option>
            </select>
        </div>

        <!-- Timer Settings -->
        <div class="section">
            <h2>Timer Settings</h2>

            <!-- T1 -->
            <div class="timer-row">
                <div>
                    <label for="t1-time">T1 Time (0-999s):</label>
                    <input type="number" id="t1-time" name="t1-time" min="0" max="999" step="0.01" value="2.50">
                </div>
                <div>
                    <label for="t1-angle">T1 Angle (0-180°):</label>
                    <input type="number" id="t1-angle" name="t1-angle" min="0" max="180" value="90">
                </div>
            </div>

            <!-- T2 -->
            <div class="timer-row">
                <div>
                    <label for="t2-time">T2 Time (0-999s):</label>
                    <input type="number" id="t2-time" name="t2-time" min="0" max="999" step="0.01" value="2.50">
                </div>
                <div>
                    <label for="t2-angle">T2 Angle (0-180°):</label>
                    <input type="number" id="t2-angle" name="t2-angle" min="0" max="180" value="90">
                </div>
            </div>

            <!-- T3 -->
            <div class="timer-row">
                <div>
                    <label for="t3-time">T3 Time (0-999s):</label>
                    <input type="number" id="t3-time" name="t3-time" min="0" max="999" step="0.01" value="2.50">
                </div>
                <div>
                    <label for="t3-angle">T3 Angle (0-180°):</label>
                    <input type="number" id="t3-angle" name="t3-angle" min="0" max="180" value="90">
                </div>
            </div>

            <!-- T4 -->
            <div class="timer-row">
                <div>
                    <label for="t4-time">T4 Time (0-999s):</label>
                    <input type="number" id="t4-time" name="t4-time" min="0" max="999" step="0.01" value="2.50">
                </div>
                <div>
                    <label for="t4-angle">T4 Angle (0-180°):</label>
                    <input type="number" id="t4-angle" name="t4-angle" min="0" max="180" value="90">
                </div>
            </div>
        </div>

        <!-- DT Settings -->
        <div class="section">
            <h2>DT Settings</h2>
            <label for="dt-servo-position">DT Servo Position (0-180°):</label>
            <input type="number" id="dt-servo-position" name="dt-servo-position" min="0" max="180" value="90">

            <label for="auto-dt-altitude">Auto DT Max Altitude (0-1000m):</label>
            <input type="number" id="auto-dt-altitude" name="auto-dt-altitude" min="0" max="1000" value="0">

            <label for="auto-dt-speed">Auto DT Max Vertical Speed (-10 to 0 m/s):</label>
            <input type="number" id="auto-dt-speed" name="auto-dt-speed" min="-10" max="0" step="0.1" value="0">
        </div>

        <!-- Auto DT Features -->
        <div class="section">
            <h2>Auto DT Features</h2>
            <div class="checkbox-label">
                <input type="checkbox" id="flip-detection" name="flip-detection">
                <label for="flip-detection">Flip Detection</label>
            </div>
            <div class="checkbox-label">
                <input type="checkbox" id="loop-detection" name="loop-detection">
                <label for="loop-detection">Loop Detection</label>
            </div>
            <div class="checkbox-label">
                <input type="checkbox" id="max-altitude" name="max-altitude">
                <label for="max-altitude">Max Altitude (m):</label>
                <input type="number" id="max-altitude-value" name="max-altitude-value" min="0" max="1000" value="0" style="width: 100px; margin-left: 10px;">
            </div>
            <div class="checkbox-label">
                <input type="checkbox" id="max-distance" name="max-distance">
                <label for="max-distance">Max Distance (m):</label>
                <input type="number" id="max-distance-value" name="max-distance-value" min="0" max="10000" value="0" style="width: 100px; margin-left: 10px;">
            </div>
        </div>

        <!-- Submit Button -->
        <input type="submit" value="SAVE">
    </form>

    <script>
        // Form submission handler
        function submitForm(event) {
            event.preventDefault(); // Prevent default form submission

            // Collect form data
            var formData = new FormData(event.target);

            // Convert form data to JSON
            var formDataJSON = {};
            formData.forEach(function(value, key) {
                formDataJSON[key] = value;
            });

            // Send data to Flutter or server
            // For example: window.FormChannel.postMessage(JSON.stringify(formDataJSON));
            console.log(JSON.stringify(formDataJSON));
        }
    </script>

</body>
</html>
