<!DOCTYPE html>
<html>

<h1 style="color:green;"> IoT Course</h1>

<form method="post" action="<?php echo $_SERVER['PHP_SELF'];?>">
	Click to turn ON: <input type="submit" name="fname" value="on">
	<p> </p>
	Click to Turn OFF: <input type="submit" name="fname" value="off">
	<p> </p>
</form>
<!-- Using PHP Script: passing fname via POST_METHOD-->
<?php
$var1 = " ";
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $var1 = $_POST["fname"];
    if (empty($var1)) {
        $var1= " ";
    }
    else {
    $var1 = $_POST["fname"];
    echo "Last time you clicked was: $var1";
    }
}
$myfile = fopen("tp.txt", "w") or die("Unable to open file");
fwrite($myfile, $var1);
fclose($myfile);
?>
<p>Check the file https://josephwalkup.net/api/tp.txt</p>
</html>
