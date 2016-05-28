<%@ page import = "java.sql.*" language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>Insert title here</title>
</head>
<body>
<%
request.setCharacterEncoding("UTF-8");
String uid = request.getParameter("uid");
String upassword = request.getParameter("upassword");
String uname =request.getParameter("uname");
String sql = "";
Connection con = null;
Statement stmt = null;
ResultSet rs = null;
try{
	Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
	con = DriverManager.getConnection("jdbc:sqlserver://localhost:1433; DatabaseName=qimiaoyuan","sa","sa");
	stmt = con.createStatement();
	rs = stmt.executeQuery("select * from users where id = '"+uid+"'");
	 if(!rs.next())
	{
		sql = "insert into users (id,name,pwd,email) values ('"+uid+"','"+uname+"','"+upassword+"','14"+"')";
		if(stmt.executeUpdate(sql) == 1)
		{
			out.println("<script language='javascript'> alert('注册成功！'); </script>");
		    response.setHeader("refresh", "1;url=Landing.html");
		}
		else
		{
			out.println("<script language='javascript'> alert('注册失败！请重新注册'); </script>");
		    response.setHeader("refresh", "1;url=newuser.jsp");
	    }
    }
	else
	{
		out.println("<script language='javascript'> alert('注册失败！请重新注册'); </script>");
	    response.setHeader("refresh", "1;url=newuser.jsp");
    }
	 
			
}catch(ClassNotFoundException e){
	out.println("驱动类无法找到！");
	throw new RuntimeException (e);
}catch(SQLException e){
	out.println("数据库访问异常！");
	throw new RuntimeException (e);
}finally{
	try{
		if(rs != null)
			rs.close();
		if(stmt != null)
			stmt.close();
		if(con != null)
			con.close();
	}catch(SQLException e){
		out.println("关闭连接时发生异常！");
	}
}
%>

</body>
</html>