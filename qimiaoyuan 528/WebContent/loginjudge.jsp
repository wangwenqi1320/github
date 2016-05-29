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
String uid = request.getParameter("uid");
String upassword = request.getParameter("upassword");
String uname = "  ";
Connection con = null;
Statement stmt = null;
ResultSet rs = null;
try{
	Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
	con = DriverManager.getConnection("jdbc:sqlserver://localhost:1433; DatabaseName=qimiaoyuan","sa","sa");
	stmt = con.createStatement();
	rs = stmt.executeQuery("select * from users where id = '"+uid+"'");
	while(rs.next())
	{
		if(upassword.equals(rs.getString("pwd")))
		{
			uname = rs.getString("name");
			break;
		}
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

if(!uname.equals("  "))
{
	session.setAttribute("sessionname",uid);
	%>
	<jsp:forward page ="try.jsp"/>
<% 
}
else
{
	out.println("<script language='javascript'> alert('登陆失败.'); </script>");
    response.setHeader("refresh", "1;url=Landing.html");

}
%>

</body>
</html>