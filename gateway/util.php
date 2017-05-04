<?php
class AES_128_CBC {
    private $_key = "qqhaois103194669";
    private $_iv = "qqhaois103194669";

    function __construct($key, $iv) {
        $this->_key = $key;
        $this->_iv == $iv;
    }

    public function decode($data){
        return mcrypt_decrypt(MCRYPT_RIJNDAEL_128, $this->_key, base64_decode($data),MCRYPT_MODE_CBC, $this->_iv);
    }

    public function encode($data){
        return base64_encode(mcrypt_encrypt(MCRYPT_RIJNDAEL_128, $this->_key, $data, MCRYPT_MODE_CBC, $this->_iv));
    }
}

function dnf_verification($post_data, $arg_count) {
	if(count($post_data) != $arg_count) {
                dnf_output("dataerror". count($post_data));
        }
}

function dnf_output($str) {
	global $aes;
        echo $aes->encode($str);
	exit;
}

function hex2tobin( $str ) {
	$sbin = "";
	$len = strlen( $str );
	for ( $i = 0; $i < $len; $i += 2 ) {
		$sbin .= pack( "H*", substr( $str, $i, 2 ) );
	}
	return $sbin;
}
?>
