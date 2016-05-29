<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
    <title>My JSP 'try.jsp' starting page</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->

<style>

</style>
  </head>
  <%String s=(String)session.getAttribute("sessionname");
  session.setAttribute("id",s ); %>
   <!-- <frameset cols="0%,80%,*"> -->
    <!-- <frame name="col1" scrolling="no"> -->
    <frameset rows="17%,*">
    <frame src="2.html" name="top" scrolling="no">
    <frameset cols="30%,*">
    <frame src="3.jsp" name="second" scrolling="no">
    <frame src="4.jsp" name="third" scrolling="auto">
    </frameset>
    </frameset>
   <!--  </frameset> -->
</html>
