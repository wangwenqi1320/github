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
    
    <title>My JSP 'update.jsp' starting page</title>
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

  </head>
  
  <body>
    <%
    String time=(String)session.getAttribute("time");
  request.setCharacterEncoding("utf-8");
  String id=(String)session.getAttribute("id2");
  String title=request.getParameter("title");
  String texts=request.getParameter("texts");
  response.setCharacterEncoding("utf-8");
   String driverName = "com.microsoft.sqlserver.jdbc.SQLServerDriver";   //加载JDBC驱动  
	String dbURL = "jdbc:sqlserver://localhost:1433; DatabaseName=qimiaoyuan";   //连接服务器和数据库 
	String userName = "sa";   //默认用户名  
	String userPwd = "sa";   //密码   
    Class.forName(driverName);   
  	Connection con = DriverManager.getConnection(dbURL, userName, userPwd);      
	Statement stmt=con.createStatement();
  String sql="update note set title='"+title+"',text='"+texts+"' where id='"+id+"' and time='"+time+"'"; 
  int i=stmt.executeUpdate(sql);//执行SQL语句并返回结果
	if(i==1)
	{
	out.println("<script language='javaScript'> alert('修改成功，点击确定后自动跳到主页。');</script>");
	response.setHeader("refresh","1;url=try.jsp");
	}else{
		out.println("<script language='javaScript'> alert('修改失败，点击确定后自动跳到主页。');</script>");
		response.setHeader("refresh","1;url=try.jsp");
	}
  stmt.close();
  con.close();
  %>
  </body>
</html>
