-- MySQL dump 10.16  Distrib 10.1.38-MariaDB, for debian-linux-gnueabihf (armv7l)
--
-- Host: localhost    Database: alpen
-- ------------------------------------------------------
-- Server version	10.1.38-MariaDB-0+deb9u1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `ipc`
--

DROP TABLE IF EXISTS `ipc`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ipc` (
  `message_id` int(11) NOT NULL AUTO_INCREMENT,
  `sender` varchar(32) DEFAULT NULL,
  `receiver` varchar(32) NOT NULL,
  `message` varchar(1024) DEFAULT NULL,
  `created` timestamp NULL DEFAULT NULL,
  `received` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`message_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ipc`
--

LOCK TABLES `ipc` WRITE;
/*!40000 ALTER TABLE `ipc` DISABLE KEYS */;
/*!40000 ALTER TABLE `ipc` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `job_type`
--

DROP TABLE IF EXISTS `job_type`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `job_type` (
  `job_type_id` int(11) NOT NULL,
  `token` varchar(32) NOT NULL,
  `description` varchar(1024) DEFAULT NULL,
  PRIMARY KEY (`job_type_id`),
  UNIQUE KEY `job_type_token_uindex` (`token`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `job_type`
--

LOCK TABLES `job_type` WRITE;
/*!40000 ALTER TABLE `job_type` DISABLE KEYS */;
INSERT INTO `job_type` VALUES (1,'PARK','Park job'),(2,'GET','Load a tote'),(3,'PUT','Unload a tote');
/*!40000 ALTER TABLE `job_type` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `jobs`
--

DROP TABLE IF EXISTS `jobs`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `jobs` (
  `job_id` int(11) NOT NULL AUTO_INCREMENT,
  `order_id` int(11) NOT NULL,
  `shuttle_id` int(11) DEFAULT NULL,
  `job_type_id` int(11) NOT NULL,
  `state` int(11) NOT NULL DEFAULT '0',
  `position_id` int(11) DEFAULT NULL,
  `level_id` int(11) DEFAULT NULL,
  `sequence` int(11) DEFAULT NULL,
  PRIMARY KEY (`job_id`),
  KEY `jobs_order_id_fk` (`order_id`),
  KEY `jobs_shuttles_shuttle_id_fk` (`shuttle_id`),
  KEY `jobs_job_type_job_type_id_fk` (`job_type_id`),
  CONSTRAINT `jobs_job_type_job_type_id_fk` FOREIGN KEY (`job_type_id`) REFERENCES `job_type` (`job_type_id`),
  CONSTRAINT `jobs_order_id_fk` FOREIGN KEY (`order_id`) REFERENCES `orders` (`order_id`) ON DELETE CASCADE,
  CONSTRAINT `jobs_shuttles_shuttle_id_fk` FOREIGN KEY (`shuttle_id`) REFERENCES `shuttles` (`shuttle_id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `jobs`
--

LOCK TABLES `jobs` WRITE;
/*!40000 ALTER TABLE `jobs` DISABLE KEYS */;
INSERT INTO `jobs` VALUES (1,1,NULL,2,1,1,100,1),(2,1,NULL,3,1,1,200,2);
/*!40000 ALTER TABLE `jobs` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `order_type`
--

DROP TABLE IF EXISTS `order_type`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `order_type` (
  `order_type_id` int(11) NOT NULL,
  `token` varchar(32) NOT NULL,
  `description` varchar(1024) DEFAULT NULL,
  PRIMARY KEY (`order_type_id`),
  UNIQUE KEY `order_type_token_uindex` (`token`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `order_type`
--

LOCK TABLES `order_type` WRITE;
/*!40000 ALTER TABLE `order_type` DISABLE KEYS */;
INSERT INTO `order_type` VALUES (1,'TRANSPORT',NULL),(2,'CHARGE',NULL);
/*!40000 ALTER TABLE `order_type` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `orders`
--

DROP TABLE IF EXISTS `orders`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `orders` (
  `order_id` int(11) NOT NULL AUTO_INCREMENT,
  `order_type_id` int(11) NOT NULL,
  `priority` int(11) NOT NULL,
  `shuttle_id` int(11) DEFAULT NULL,
  `state` int(11) NOT NULL DEFAULT '1',
  `sequence` int(11) NOT NULL DEFAULT '1',
  PRIMARY KEY (`order_id`),
  KEY `orders_order_type_order_type_id_fk` (`order_type_id`),
  CONSTRAINT `orders_order_type_order_type_id_fk` FOREIGN KEY (`order_type_id`) REFERENCES `order_type` (`order_type_id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `orders`
--

LOCK TABLES `orders` WRITE;
/*!40000 ALTER TABLE `orders` DISABLE KEYS */;
INSERT INTO `orders` VALUES (1,1,1,NULL,1,1),(2,1,3,NULL,1,2),(3,1,2,NULL,1,2);
/*!40000 ALTER TABLE `orders` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `shuttle_battery_level`
--

DROP TABLE IF EXISTS `shuttle_battery_level`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `shuttle_battery_level` (
  `shuttle_battery_level_id` int(11) NOT NULL,
  `token` varchar(32) NOT NULL,
  `decription` varchar(1024) DEFAULT NULL,
  PRIMARY KEY (`shuttle_battery_level_id`),
  UNIQUE KEY `shuttle_battery_level_token_uindex` (`token`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `shuttle_battery_level`
--

LOCK TABLES `shuttle_battery_level` WRITE;
/*!40000 ALTER TABLE `shuttle_battery_level` DISABLE KEYS */;
INSERT INTO `shuttle_battery_level` VALUES (0,'UNKNOWN','Shuttle did not transmit its battery charge'),(1,'CRITICAL','Shuttle immediatly needs to be charged and cannot finish its current orders'),(2,'LOW','Shuttle battery is low (shuttle can still finish its current orders)'),(3,'NORMAL','Shuttle battery is sufficiently charged'),(4,'FULL','Shuttle battery is fully charged');
/*!40000 ALTER TABLE `shuttle_battery_level` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `shuttle_mode`
--

DROP TABLE IF EXISTS `shuttle_mode`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `shuttle_mode` (
  `shuttle_mode_id` int(11) NOT NULL,
  `token` varchar(32) NOT NULL,
  `description` varchar(1024) DEFAULT NULL,
  PRIMARY KEY (`shuttle_mode_id`),
  UNIQUE KEY `shuttle_mode_token_uindex` (`token`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `shuttle_mode`
--

LOCK TABLES `shuttle_mode` WRITE;
/*!40000 ALTER TABLE `shuttle_mode` DISABLE KEYS */;
INSERT INTO `shuttle_mode` VALUES (0,'OUTOFORDER','Shuttle can not receive orders, neither automatically nor manually'),(1,'MANUAL','Shuttle will not automatically receive new orders'),(2,'AUTOMATIC','Shuttle is allowed to automatically received new orders');
/*!40000 ALTER TABLE `shuttle_mode` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `shuttle_state`
--

DROP TABLE IF EXISTS `shuttle_state`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `shuttle_state` (
  `shuttle_state_id` int(11) NOT NULL,
  `token` varchar(32) NOT NULL,
  `description` varchar(1024) DEFAULT NULL,
  PRIMARY KEY (`shuttle_state_id`),
  UNIQUE KEY `shuttle_state_token_uindex` (`token`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `shuttle_state`
--

LOCK TABLES `shuttle_state` WRITE;
/*!40000 ALTER TABLE `shuttle_state` DISABLE KEYS */;
INSERT INTO `shuttle_state` VALUES (0,'SUSPENDED','Shuttle has an error'),(1,'READY','Shuttle is ready to receive new orders'),(2,'OCCUPIED','Shuttle is currently executing orders');
/*!40000 ALTER TABLE `shuttle_state` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `shuttle_type`
--

DROP TABLE IF EXISTS `shuttle_type`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `shuttle_type` (
  `shuttle_type_id` int(11) NOT NULL,
  `container_limit` int(11) NOT NULL DEFAULT '1',
  `token` varchar(32) NOT NULL,
  `description` varchar(1024) DEFAULT NULL,
  PRIMARY KEY (`shuttle_type_id`),
  UNIQUE KEY `shuttle_type_token_uindex` (`token`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `shuttle_type`
--

LOCK TABLES `shuttle_type` WRITE;
/*!40000 ALTER TABLE `shuttle_type` DISABLE KEYS */;
INSERT INTO `shuttle_type` VALUES (0,0,'INVALID','Dummy default value'),(1,1,'ALPEN_SHUTTLE','Alpen shuttle with LAM for 10 loading units'),(2,1,'OPEN_SHUTTLE','OS50 with LAM for 1 loading unit');
/*!40000 ALTER TABLE `shuttle_type` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `shuttles`
--

DROP TABLE IF EXISTS `shuttles`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `shuttles` (
  `shuttle_id` int(11) NOT NULL,
  `shuttle_type_id` int(11) NOT NULL DEFAULT '0',
  `shuttle_mode_id` int(11) NOT NULL DEFAULT '0',
  `shuttle_state_id` int(11) NOT NULL DEFAULT '0',
  `shuttle_battery_level_id` int(11) NOT NULL DEFAULT '0',
  `level_id` int(11) DEFAULT NULL,
  `position_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`shuttle_id`),
  KEY `shuttles_shuttle_mode_shuttle_mode_id_fk` (`shuttle_mode_id`),
  KEY `shuttles_shuttle_state_shuttle_state_id_fk` (`shuttle_state_id`),
  KEY `shuttles_shuttle_type_shuttle_type_id_fk` (`shuttle_type_id`),
  KEY `shuttles_shuttle_battery_level_shuttle_battery_level_id_fk` (`shuttle_battery_level_id`),
  CONSTRAINT `shuttles_shuttle_battery_level_shuttle_battery_level_id_fk` FOREIGN KEY (`shuttle_battery_level_id`) REFERENCES `shuttle_battery_level` (`shuttle_battery_level_id`),
  CONSTRAINT `shuttles_shuttle_mode_shuttle_mode_id_fk` FOREIGN KEY (`shuttle_mode_id`) REFERENCES `shuttle_mode` (`shuttle_mode_id`),
  CONSTRAINT `shuttles_shuttle_state_shuttle_state_id_fk` FOREIGN KEY (`shuttle_state_id`) REFERENCES `shuttle_state` (`shuttle_state_id`),
  CONSTRAINT `shuttles_shuttle_type_shuttle_type_id_fk` FOREIGN KEY (`shuttle_type_id`) REFERENCES `shuttle_type` (`shuttle_type_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `shuttles`
--

LOCK TABLES `shuttles` WRITE;
/*!40000 ALTER TABLE `shuttles` DISABLE KEYS */;
INSERT INTO `shuttles` VALUES (1,2,2,1,1,1,201),(2,2,2,1,3,1,199),(3,2,0,0,0,-1,-1);
/*!40000 ALTER TABLE `shuttles` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `station_interaction`
--

DROP TABLE IF EXISTS `station_interaction`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `station_interaction` (
  `station_interaction_id` int(11) NOT NULL,
  `token` varchar(32) NOT NULL,
  `description` varchar(1024) DEFAULT NULL,
  PRIMARY KEY (`station_interaction_id`),
  UNIQUE KEY `station_interaction_token_uindex` (`token`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `station_interaction`
--

LOCK TABLES `station_interaction` WRITE;
/*!40000 ALTER TABLE `station_interaction` DISABLE KEYS */;
INSERT INTO `station_interaction` VALUES (1,'GET','Station allows pickup of containers'),(2,'PUT','Station allows put down of containers'),(3,'GET_PUT','At this station containers can be picked up or put down');
/*!40000 ALTER TABLE `station_interaction` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `station_type`
--

DROP TABLE IF EXISTS `station_type`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `station_type` (
  `station_type_id` int(11) NOT NULL,
  `token` varchar(32) NOT NULL,
  `description` varchar(1024) DEFAULT NULL,
  PRIMARY KEY (`station_type_id`),
  UNIQUE KEY `station_type_token_uindex` (`token`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `station_type`
--

LOCK TABLES `station_type` WRITE;
/*!40000 ALTER TABLE `station_type` DISABLE KEYS */;
INSERT INTO `station_type` VALUES (1,'CONVEYOR','Conveyor endpoint'),(2,'RACK','Virtual station for rack');
/*!40000 ALTER TABLE `station_type` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `stations`
--

DROP TABLE IF EXISTS `stations`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `stations` (
  `station_id` int(11) NOT NULL,
  `station_type_id` int(11) NOT NULL,
  `state` int(11) NOT NULL DEFAULT '0',
  `level_id` int(11) DEFAULT NULL,
  `position_id` int(11) DEFAULT NULL,
  `interaction_id` int(11) NOT NULL,
  PRIMARY KEY (`station_id`),
  KEY `stations_station_type_station_type_id_fk` (`station_type_id`),
  KEY `stations_station_interaction_station_interaction_id_fk` (`interaction_id`),
  CONSTRAINT `stations_station_interaction_station_interaction_id_fk` FOREIGN KEY (`interaction_id`) REFERENCES `station_interaction` (`station_interaction_id`),
  CONSTRAINT `stations_station_type_station_type_id_fk` FOREIGN KEY (`station_type_id`) REFERENCES `station_type` (`station_type_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `stations`
--

LOCK TABLES `stations` WRITE;
/*!40000 ALTER TABLE `stations` DISABLE KEYS */;
INSERT INTO `stations` VALUES (1,1,1,1,100,1),(61,2,1,1,200,3);
/*!40000 ALTER TABLE `stations` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-07-06 14:05:57