<?php
Require("config.php");
//Require("rsa.php");
Require("util.php");

$aes = new AES_128_CBC($key, $iv);

$tmp = explode('&', $aes->decode(file_get_contents("php://input")));

if(strcasecmp(md5($tmp[0]), substr($tmp[1],0,32)) != 0) {
    dnf_output("md5error");
}

$post_data = explode('|', $tmp[0]);

$dbcon = Mysql_connect($server, $dbuser, $dbpass);
if (!$dbcon){
	dnf_output("Mysql Connect Error");
}

switch($post_data[0])
{
	case "login":
		dnf_login($post_data);
        case "regedit":
                dnf_regedit($post_data);
        case "forget":
                dnf_forget($post_data);
        case "repasswd":
		dnf_repasswd($post_data);
}

function dnf_login($post_data){
        global $private_key;
	dnf_verification($post_data, 4);
	$username = $post_data[1];
	$password = $post_data[2];
	$mac = $post_data[3];
	$ip = $_SERVER['REMOTE_ADDR'];
	$sql = Mysql_query("select * from d_taiwan.accounts where accountname='$username' and password='$password'");

	if(Mysql_num_rows($sql)==0){
		dnf_output("Username or password Error");
                exit;
	}else{
		$str = Mysql_fetch_array($sql);
		$uid = $str['UID'];
		
		$sql_not = Mysql_query("select * from d_taiwan.member_punish_info where m_id='$uid'");
		if(Mysql_num_rows($sql_not)){ 
			dnf_output("login not");
		}
		
		$sql_login = Mysql_query("select * from d_gmaster.login where uid='$uid'");
		$time = date("y-m-d h:i:s",time());
		
		if(Mysql_num_rows($sql_login)==0){
			Mysql_query("insert into d_gmaster.login (uid,reg_time,login_time,mac,ip) VALUES ('$uid','$time','$time','$mac','$ip')");
		}else{
			$str_login = Mysql_fetch_array($sql_login);
			$login_num = $str_login['login_num'] + 1;
			Mysql_query("update d_gmaster.login set login_time='$time',login_num='$login_num',mac='$mac',ip='$ip' where uid='$uid'");
		}
			
		$data = sprintf("%08x010101010101010101010101010101010101010101010101010101010101010155914510010403030101",$uid);
		$data = hex2tobin($data);
		$encrypted = "";
		$pi_key =  openssl_pkey_get_private($private_key);
		openssl_private_encrypt($data,$encrypted,$pi_key);
		$encrypted = base64_encode($encrypted);
	 	Mysql_query("update d_taiwan.limit_create_character set count=0 where m_id='$uid'");//取消角色创建限制
		dnf_output($encrypted);
	}
}

function dnf_regedit($post_data){
	dnf_verification($post_data, 4);
	$username = $post_data[1];
	$password = $post_data[2];
	$qq = $post_data[3];
	$sql = Mysql_query("select * from d_taiwan.accounts where accountname='$username'");
		
	if(Mysql_num_rows($sql)==0){
		$sql = Mysql_query("select * from d_taiwan.accounts order by UID desc limit 1");
		if(Mysql_num_rows($sql)==0){
			$uid = $inituid;
		}else{
			$str = Mysql_fetch_array($sql);
			$uid = $str['UID'] + 1;
		}
		$time = date("y-m-d h:i:s",time());
		if(Mysql_query("insert into d_taiwan.accounts (UID,accountname,password,qq) VALUES ('$uid','$username','$password','$qq')")){
			Mysql_query("insert into d_taiwan.limit_create_character (m_id) VALUES ('$uid')");
			Mysql_query("insert into d_taiwan.member_info (m_id,user_id) VALUES ('$uid','$uid')");
			Mysql_query("insert into d_taiwan.member_join_info (m_id) VALUES ('$uid')");
			Mysql_query("insert into d_taiwan.member_miles (m_id) VALUES ('$uid')");
			Mysql_query("insert into d_taiwan.member_white_account (m_id) VALUES ('$uid')");
			Mysql_query("insert into taiwan_login.member_login (m_id) VALUES ('$uid')");
			Mysql_query("insert into taiwan_billing.cash_cera (account,cera,mod_date,reg_date) VALUES ('$uid','$regdb','$time','$time')");
			Mysql_query("insert into taiwan_billing.cash_cera_point (account,cera_point,reg_date,mod_date) VALUES ('$uid','$regdd','$time','$time')");
			Mysql_query("insert into taiwan_cain_2nd.member_avatar_coin (m_id) VALUES ('$uid')");
			dnf_output( "success");
		}else{
			dnf_output("fail");
		}
	}else{
		dnf_output("repeat");
    }
}

function dnf_forget($post_data) {
        dnf_verification($post_data, 4);

	$username = $post_data[1];
	$password = $post_data[2];
	$qq = $post_data[3];
	$sql = Mysql_query("select * from d_taiwan.accounts where accountname='$username' and qq='$qq'");

	if(Mysql_num_rows($sql)==0){
		dnf_output("fail");
	}
	if(Mysql_query("update d_taiwan.accounts set password='$password' where accountname='$username'")){
		dnf_output("success");
	}else{
		dnf_output("fail");
	}
}

function dnf_repasswd($post_data) {
        dnf_verification($post_data, 4);

	$username = $post_data[1];
	$password = $post_data[2];
	$newpassword = $post_data[3];
	
	$sql = Mysql_query("select * from d_taiwan.accounts where accountname='$username' and password='$password'");

	if(Mysql_num_rows($sql)==0){
		dnf_output("passworderror");
	}
	if(Mysql_query("update d_taiwan.accounts set password='$newpassword' where accountname='$username'")){
		dnf_output("success");
	}else{
		dnf_putput("fail");
	}
}
?>
