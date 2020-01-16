package com.my.edigits.entity;

import java.util.Date;

/**
 * Mysql数据库对应字段
 */
public class Usr {

    private String username;
    private String nickname;
    private String str;
    private Integer hstep;
    private Integer cstep;
    private Integer ccnt;
    private Double score;
    private Date date;

    public Usr() {

    }

    public Usr(String username) {
        this.username = username;
    }

    public Usr(String username, String str, Integer hstep, Integer cstep, Integer ccnt, Double score, Date date) {
        this.username = username;
        this.str = str;
        this.hstep = hstep;
        this.cstep = cstep;
        this.ccnt = ccnt;
        this.score = score;
        this.date = date;
    }

    public Usr(String username, String nickname, String str, Integer hstep, Integer cstep, Integer ccnt, Double score, Date date) {
        this.username = username;
        this.nickname = nickname;
        this.str = str;
        this.hstep = hstep;
        this.cstep = cstep;
        this.ccnt = ccnt;
        this.score = score;
        this.date = date;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getNickname() {
        return nickname;
    }

    public void setNickname(String nickname) {
        this.nickname = nickname;
    }

    public String getStr() {
        return str;
    }

    public void setStr(String str) {
        this.str = str;
    }

    public Integer getHstep() {
        return hstep;
    }

    public void setHstep(Integer hstep) {
        this.hstep = hstep;
    }

    public Integer getCstep() {
        return cstep;
    }

    public void setCstep(Integer cstep) {
        this.cstep = cstep;
    }

    public Integer getCcnt() {
        return ccnt;
    }

    public void setCcnt(Integer ccnt) {
        this.ccnt = ccnt;
    }

    public Double getScore() {
        return score;
    }

    public void setScore(Double score) {
        this.score = score;
    }

    public Date getDate() {
        return date;
    }

    public void setDate(Date date) {
        this.date = date;
    }

    @Override
    public String toString() {
        return "Usr{" +
                "username='" + username + '\'' +
                ", nickname='" + nickname + '\'' +
                ", str='" + str + '\'' +
                ", hstep=" + hstep +
                ", cstep=" + cstep +
                ", ccnt=" + ccnt +
                ", score=" + score +
                ", date=" + date +
                '}';
    }
}