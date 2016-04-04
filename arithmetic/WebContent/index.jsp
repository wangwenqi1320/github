<%@ page language="java" contentType="text/html; charset=utf-8"

    pageEncoding="utf-8"%>
<%@ page import="test4.*"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>答题</title>
    <meta http-equiv="Content-Type" content="text/html; charset=gb2312" />
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->
  </head>
  
  <body background="images/A2.jpg">

   <%
   String[] s=new String[30];
   float k[]=new float[30];
   Calculate a=new Calculate();
 
   request.setCharacterEncoding("UTF-8");
   String[] function = request.getParameterValues("function");
   String TopNumber,BaseNumber;
   TopNumber=request.getParameter("TopNumber");
   BaseNumber=request.getParameter("BaseNumber");
    a.SetValue(a.StrToNum(TopNumber),a.StrToNum(BaseNumber));
   if(function!=null){
   for(int i=0;i<function.length;i++){
   	if(function[i].equals("1"))
   	{
   		a.SetValue1(1);
   	}
   	if(function[i].equals("2"))
   	{
   		a.SetValue2(1);
   	}
   	if(function[i].equals("3"))
   	{
   		a.SetValue3(0);
   	}
   	}
   }
   	
  
    %>
   <form action="MyJsp.jsp" method="post">
   <center>
   <%
     a.main();
     float temp;
     String[] se=new String[30];
     for(int i=0;i<30;i++){
     s[i]=a.cs(i);
   		se[i]="name";
   		se[i]=se[i]+i;
     k[i]=a.css(i);
     out.print("<tr>"+s[i]+"</tr>");
     out.println("<br>");
    
     
   %>   
   <input type="text" name=<%=se[i] %>><br>
   <%
       } 
		session.setAttribute( "v1",s);
		session.setAttribute( "v2",k); 
    %>
    <br><input type="submit" name="submit" value="提交">
    
    <%
    
   
    %>
     </center>
  </form>
  
  
   
    
  </body>
</html>
