-- phpMyAdmin SQL Dump
-- version 4.8.2
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: 2018-12-27 13:57:14
-- 服务器版本： 10.1.34-MariaDB
-- PHP Version: 7.2.8

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `egdb`
--

-- --------------------------------------------------------

--
-- 表的结构 `usrscore`
--

CREATE TABLE `usrscore` (
  `username` varchar(100) NOT NULL,
  `nickname` varchar(100) DEFAULT NULL,
  `str` varchar(10) NOT NULL,
  `hstep` int(11) NOT NULL,
  `cstep` int(11) NOT NULL,
  `ccnt` int(11) NOT NULL,
  `score` float NOT NULL,
  `date` datetime NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- 转存表中的数据 `usrscore`
--

INSERT INTO `usrscore` (`username`, `nickname`, `str`, `hstep`, `cstep`, `ccnt`, `score`, `date`) VALUES
('1545908614252', NULL, '873625401', 19, 20, 2, 97.154, '2018-12-27 19:03:55'),
('1545908998351', NULL, '065238417', 22, 23, 1, 98.2377, '2018-12-27 19:10:14'),
('1545909309695', NULL, '261804375', 18, 19, 2, 97.1109, '2018-12-27 19:15:33'),
('1545909455888', NULL, '758314620', 22, 23, 1, 98.256, '2018-12-27 19:17:50');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `usrscore`
--
ALTER TABLE `usrscore`
  ADD PRIMARY KEY (`username`),
  ADD KEY `username` (`username`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
