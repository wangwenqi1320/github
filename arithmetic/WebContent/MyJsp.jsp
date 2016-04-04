<%@ page language="java" import="java.util.*" pageEncoding="gb2312" contentType="text/html; charset=gb2312"%>
<%@ page import="test4.*"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>结果</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->

  </head>
  
 <body background="images/A3.jpg">
  <% request.setCharacterEncoding("UTF-8");%>
  <center>
  <%
   
    String[] name=new String[30];
    String[] sum=new String[30];
    Calculate a=new Calculate();
    float sum1[]=new float[30];
    int right=0;
    String[] s= (String[])session.getAttribute("v1");
    float[] k=(float[])session.getAttribute("v2");
  
    for(int i=0;i<30;i++)
        sum1[i]=0;
    for(int i=0;i<30;i++){
	    name[i]="name";
	    name[i]=name[i]+i;
	    
	    sum[i]=request.getParameter(name[i]);
	    //sum[i]=request.getParameterValues(name[i])";
	    out.print(s[i]);
	    out.print("<tr>"+sum[i]+"</tr>");
	    if(sum[i]=="")
	       out.print("未回答！");
	    else{
		    if(((int)(k[i]*100))%100!=0)
		       sum1[i]=a.StrToFloat1(sum[i]);
		    else
		       sum1[i]=a.StrToFloat(sum[i]);
		    if(Math.abs(sum1[i]*100-k[i]*100)<4){
		       out.print(" 回答正确！");
		       right++;
		    }
		    else
		       out.print(" 回答错误，正确答案是： "+k[i]);
	    }   
	    
	     out.println("<br>");
    }
    out.print("总共做对 "+right+" 题，正确率为："+(right/30.0)*100+" %");
  %><br>
   <input type="button" value="返回首页" onClick="window.location.href='MyHtml.html'">
   <input type="button" value="关闭" onClick="window.close();">
    </center>
  </body>
</html>
