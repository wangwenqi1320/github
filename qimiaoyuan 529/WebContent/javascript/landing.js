function checkNULL()
  {
	  var uid = document.form.uid.value;
	  var upassword = document.form.upassword.value;
	 	  if(uid == "请输入你的登录名" || upassword == "请输入你的密码")
		{
		  alert("输入不能为空！")
		  return false;
         }
	  else 
		  {
		  return true;
          }
 }