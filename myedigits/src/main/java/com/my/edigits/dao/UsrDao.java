package com.my.edigits.dao;

import com.my.edigits.entity.Usr;
import com.my.edigits.utils.SqlSessionFactoryUtils;
import org.apache.ibatis.session.SqlSession;

import java.util.List;

/**
 * 用户DAO模块
 * MyBatis框架查询
 */

public class UsrDao {

    private SqlSession sqlSession;

    private List<Usr> list;

    private Usr usr;

    private SqlSession getSession(){
        sqlSession = SqlSessionFactoryUtils.getSqlSessionFactory().openSession();
        return sqlSession;
    }

    /**
     * Get All Usr
     * @return
     */
    public List<Usr> findUsrs(){
        try {
            list = getSession().selectList("findUsrs");
        }catch (Exception e){
            e.printStackTrace();
        }finally {
            sqlSession.close();
        }
        return list;
    }
    public Usr findUsr(String username){
        try {
            usr = getSession().selectOne("findUsr", new Usr(username));
        }catch (Exception e){
            e.printStackTrace();
        }finally {
            sqlSession.close();
        }
        return usr;
    }
    /**
     *
     * @param usr
     * @return
     */
    public Usr addUsr(Usr usr){
        try{
            getSession().insert("addUsr",usr);
            sqlSession.commit();
        }catch (Exception e){
            e.printStackTrace();
        }finally {
            sqlSession.close();
        }
        return usr;
    }

    public Usr changeUsr(Usr usr){
        try {
            getSession().update("changeUsr",usr);
            sqlSession.commit();
        }catch (Exception e){
            e.printStackTrace();
        }finally {
            sqlSession.close();
        }
        return usr;
    }

}
