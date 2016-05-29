<%@ page language="java" contentType="text/html; charset=utf-8"

    pageEncoding="utf-8"%>
<%@ page import="java.sql.*" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>添加笔记</title>
</head>

<body>

  <%
    request.setCharacterEncoding("UTF-8");
      
    //获取参数的值
   String id=(String)session.getAttribute("id");
    String title=request.getParameter("title");
    String gro=request.getParameter("gro");
    String text=request.getParameter("text");   

    String time=(new java.util.Date()).toLocaleString(); 
    String submit=request.getParameter("submit"); 
    	
    //连接数据库
    String driverName = "com.microsoft.sqlserver.jdbc.SQLServerDriver";  //加载JDBC驱动    
    String dbURL = "jdbc:sqlserver://localhost:1433; DatabaseName=qimiaoyuan"; 
    //连接服务器和数据库sample    
    String userName = "sa";  //默认用户名    
    String userPwd = "sa";  //密码       
    Class.forName(driverName);   
    Connection con = DriverManager.getConnection(dbURL, userName, userPwd);      
    Statement stmt=con.createStatement();
    	
    	String sql="insert into note(id,title,text,gro,time) values('"+id+"','"+title+"','"+text+"',"+gro+",'"+time+"')";
    	int i=stmt.executeUpdate(sql); //执行SQL语句
    	if(i==1)
    	{  //已插入记录
    	out.println("<script language='javaScript'> alert('添加成功,点击确定跳转到个人页面!');</script>");
    	response.setHeader("refresh","1;url=try.jsp"); //跳转到index.jsp文件
    	}
    	else{ //没有插入记录
    	out.println("<script language='javaScript'> alert('添加失败，点击确定返回添加页面！');</script>");
    	response.setHeader("refresh","1;url=AddNote.html");//跳转到add.jsp文件重新添加
    	}
    	//关闭操作
    	stmt.close();
    	con.close();
 
    
%>
     
</body>
</html>