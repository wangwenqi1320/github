<%@ page language="java" contentType="text/html; charset=utf-8"

    pageEncoding="utf-8"%>
<%@ page import="java.sql.*" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>Insert title here</title>
</head>
<body>
<%
	request.setCharacterEncoding("UTF-8");
	//连接数据库
	 String driverName = "com.microsoft.sqlserver.jdbc.SQLServerDriver";  //加载JDBC驱动    
    String dbURL = "jdbc:sqlserver://localhost:1433; DatabaseName=qimiaoyuan"; 
    //连接服务器和数据库sample    
    String userName = "sa";  //默认用户名    
    String userPwd = "sa";  //密码       
    Class.forName(driverName);   
  	Connection con = DriverManager.getConnection(dbURL, userName, userPwd);      
	Statement stmt=con.createStatement();
	String id=(String)session.getAttribute("id");
	 String time=new String(request.getParameter("param").getBytes("ISO-8859-1"),"utf-8");
	int i=stmt.executeUpdate("delete from note where id ='"+id+"' and time ='"+time+"'");//执行SQL语句
	if(i==1)
		{ //删除成功
		out.println("<script language='javaScript'> alert('删除成功，点击确定后自动跳到个人信息！');</script>");
		response.setHeader("refresh","1;url=try.jsp"); //跳转到index.jsp文件
		}

		else{//删除不成功
		out.println("<script language='javaScript'> alert('删除失败，点击确定后自动跳到个人信息！');</script>");
		response.setHeader("refresh","1;url=try.jsp"); //跳转到index.jsp文件
		}
	    //关闭操作
	    
		con.close();
		stmt.close();
		
	%>
</body>
</html>