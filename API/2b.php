<!DOCTYPE html>
<html>

<h1 style="color:green;"> IoT Course</h1>

<h4> Adjust the sliders and submit the values</h4>
<p>Check the file: <a href="https://josephwalkup.net/api/tp2.txt" target="_blank"> https://josephwalkup.net/api/tp2.txt</a></p>
<form method="post" action="<?php echo htmlspecialchars($_SERVER['PHP_SELF']);?>">
    <!-- Slider 1: Control from 0 to 255 -->
    <label for="slider1">Slider R (0-255): </label>
    <input type="range" id="slider1" name="slider1" min="0" max="255" value="0" oninput="this.nextElementSibling.value = this.value">
    <output>0</output>
    <p></p>

    <!-- Slider 2: Control from 0 to 255 -->
    <label for="slider2">Slider G (0-255): </label>
    <input type="range" id="slider2" name="slider2" min="0" max="255" value="0" oninput="this.nextElementSibling.value = this.value">
    <output>0</output>
    <p></p>
    
    <!-- Slider 1: Control from 0 to 255 -->
    <label for="slider1">Slider B (0-255): </label>
    <input type="range" id="slider3" name="slider3" min="0" max="255" value="0" oninput="this.nextElementSibling.value = this.value">
    <output>0</output>
    <p></p>

    <!-- Submit button -->
    <input type="submit" value="Submit Values">
</form>
<?php
if ($_SERVER["REQUEST_METHOD"] == "POST") {
$slider1_value = isset($_POST["slider1"]) ? $_POST["slider1"] : 0;
$slider2_value = isset($_POST["slider2"]) ? $_POST["slider2"] : 0;
$slider3_value = isset($_POST["slider3"]) ? $_POST["slider3"] : 0;
echo "Slider 1 Value: " . $slider1_value . "<br>";
echo "Slider 2 Value: " . $slider2_value . "<br>";
echo "Slider 3 Value: " . $slider3_value . "<br>";

$myfile = fopen("tp2.txt" , "w") or die("Unable to open file");
fwrite($myfile, $slider1_value . "-");
fwrite($myfile, $slider2_value . "-");
fwrite($myfile, $slider3_value);

fcose($myfile);
}
?>
</html>
