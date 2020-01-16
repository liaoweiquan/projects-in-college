package com.my.edigits.listener;

import com.my.edigits.utils.SqlSessionFactoryUtils;

import javax.servlet.ServletContextEvent;
import javax.servlet.ServletContextListener;
import javax.servlet.annotation.WebListener;

@WebListener
public class InitSqlSessionListener implements ServletContextListener {
    @Override
    public void contextInitialized(ServletContextEvent sce) {
        SqlSessionFactoryUtils.initSqlSessionFactory();
    }

    @Override
    public void contextDestroyed(ServletContextEvent sce) {
        SqlSessionFactoryUtils.close();
    }
}
