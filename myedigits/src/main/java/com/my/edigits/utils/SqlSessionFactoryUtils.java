package com.my.edigits.utils;

import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;

import java.io.IOException;
import java.io.InputStream;

/**
 * MyBatis 数据库查询
 */
public class SqlSessionFactoryUtils {

    private static String RESOURCE = "myedigits-config.xml";

    private static SqlSessionFactory sqlSessionFactory;

    private static ThreadLocal<SqlSession> threadLocal = new ThreadLocal<SqlSession>();

    /**
     * 创建一个初始化sqlsession方法
     */
    public static void initSqlSessionFactory(){
        try {
            InputStream is = Resources.getResourceAsStream(RESOURCE);
            sqlSessionFactory = new SqlSessionFactoryBuilder().build(is);
        }catch (IOException e){
            System.out.println("Can not find config xml");
            e.printStackTrace();
        }
    }

    /**
     * 获取工厂对象的方法
     * @return
     */
    public static SqlSessionFactory getSqlSessionFactory(){
        return sqlSessionFactory;
    }

    public static void close(){
        SqlSession session = threadLocal.get();
        if(session != null){
            session.close();
            threadLocal.set(null);
        }
    }
}
