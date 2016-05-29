<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"%>
<%@ page import="java.sql.*" %>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    <style type="text/css">
    div
    {
       /* border:1px solid black;       */
       margin:0px auto;
       
       
    }
    .btns { width:100px; height:30px; color:#000;background-color:#00ccff; 1px solid black; } 
    </style>
    <title>My JSP '7.jsp' starting page</title>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
    <meta http-equiv="Content-Type" content="textarea/html; charset=utf-8">
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->
	<script type="text/jscript">
   function validate(){
		if(Form.title.value==""){
			alert("标题不能为空！");
			return false;    		
		}
		if(Form.texts.value==""){
			alert("内容不能为空！");
			return false;    		
		}
	}   
     
</script>  
  </head>
  
  <body style="background:url(images/14.jpg)">
  <h1 align="center">修改笔记</h1>
    <% request.setCharacterEncoding("utf-8");%>
  <%
  String time=new String(request.getParameter("param").getBytes("ISO-8859-1"),"utf-8");
  String id=(String)session.getAttribute("id1");
  session.setAttribute("id2", id);
  session.setAttribute("time", time);
  	Statement sql;
	ResultSet rs;
	String driverName = "com.microsoft.sqlserver.jdbc.SQLServerDriver";   //加载JDBC驱动  
	String dbURL = "jdbc:sqlserver://localhost:1433; DatabaseName=qimiaoyuan";   //连接服务器和数据库 
	String userName = "sa";   //默认用户名  
	String userPwd = "sa";   //密码  
	Connection dbConn;
	Class.forName(driverName);  
	dbConn = DriverManager.getConnection(dbURL, userName, userPwd); 
	sql=dbConn.createStatement();
	rs=sql.executeQuery("select * from note where time='"+time+"' and id='"+id+"'");
	System.out.println("Connection Successful!");   //如果连接成功 控制台输出Connection Successful! 
	rs.next();
  %>
  <form action="update.jsp" method="post" name="Form">
    <div style="background-color:#e8f3f8;width:80%;height:15%;border:1px solid black;">
    <div  style = "float:right;width:25%;height:50px;position:relative;top:16px;"  id="nowDiv" ></div>
      <p>笔记标题:
        <input name="title" type="text" size="20" value="<%=rs.getString(2)%>">
    </div>
    
    <!-- <div  style = "width:25%;height:10%;" id="nowDiv" ></div> -->
    
	<div style="background-color:#e8f3f8;width:80%;height:60%;border:1px solid black;">
        <p><br>
      笔记内容:        </p>
        <p>
          &nbsp; &nbsp; &nbsp;<textarea name="texts" cols="100" rows="10"><%=rs.getString(3)%></textarea>
          <br>
          <br>
           &nbsp; &nbsp; &nbsp;
          <input type="submit" name="submit" class="btns" onclick = "return validate()" onmouseover="this.style.background='#0099ff'" onmouseout="this.style.background='#00ccff'"  value="保存">
          &nbsp; &nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
          &nbsp; &nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
          &nbsp; &nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
	      <input type="reset" class="btns"  onmouseover="this.style.background='#0099ff'" onmouseout="this.style.background='#00ccff'"  value="重置">
        </p>
	</div>
  </form>
	  <%dbConn.close(); %>
  </body>
</html>
