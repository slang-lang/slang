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
-- Table structure for table `graph_edge_type`
--

DROP TABLE IF EXISTS `graph_edge_type`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `graph_edge_type` (
  `edge_type_id` int(11) NOT NULL,
  `token` varchar(80) NOT NULL,
  `description` varchar(80) DEFAULT NULL,
  PRIMARY KEY (`edge_type_id`),
  UNIQUE KEY `graph_edge_type_token_uindex` (`token`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `graph_edge_type`
--

LOCK TABLES `graph_edge_type` WRITE;
/*!40000 ALTER TABLE `graph_edge_type` DISABLE KEYS */;
INSERT INTO `graph_edge_type` VALUES (1,'TRAVERSABLE','Traversable edge');
/*!40000 ALTER TABLE `graph_edge_type` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `graph_edges`
--

DROP TABLE IF EXISTS `graph_edges`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `graph_edges` (
  `source_level_id` int(11) NOT NULL DEFAULT '1',
  `source_node_id` int(11) DEFAULT NULL,
  `target_level_id` int(11) NOT NULL DEFAULT '1',
  `target_node_id` int(11) DEFAULT NULL,
  `edge_type_id` int(11) DEFAULT NULL,
  `length` int(11) DEFAULT NULL,
  KEY `graph_edge_type_id_fk` (`edge_type_id`),
  CONSTRAINT `graph_edge_type_id_fk` FOREIGN KEY (`edge_type_id`) REFERENCES `graph_edge_type` (`edge_type_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `graph_edges`
--

LOCK TABLES `graph_edges` WRITE;
/*!40000 ALTER TABLE `graph_edges` DISABLE KEYS */;
INSERT INTO `graph_edges` VALUES (1,100100,1,200200,1,5),(1,200200,1,250250,1,5),(1,250250,1,300300,1,5),(1,300300,1,400400,1,5),(1,250250,1,250400,1,10);
/*!40000 ALTER TABLE `graph_edges` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `graph_node_type`
--

DROP TABLE IF EXISTS `graph_node_type`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `graph_node_type` (
  `node_type_id` int(11) NOT NULL,
  `token` varchar(32) NOT NULL,
  `description` varchar(1024) DEFAULT NULL,
  PRIMARY KEY (`node_type_id`),
  UNIQUE KEY `graph_node_type_token_uindex` (`token`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `graph_node_type`
--

LOCK TABLES `graph_node_type` WRITE;
/*!40000 ALTER TABLE `graph_node_type` DISABLE KEYS */;
INSERT INTO `graph_node_type` VALUES (0,'NODE','Basic node'),(1,'CROSSING','Crossing'),(2,'STATION','Station'),(3,'PARKING','Parking spot');
/*!40000 ALTER TABLE `graph_node_type` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `graph_nodes`
--

DROP TABLE IF EXISTS `graph_nodes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `graph_nodes` (
  `level_id` int(11) NOT NULL DEFAULT '1',
  `position_id` int(11) NOT NULL,
  `node_type_id` int(11) NOT NULL,
  `viz_x` int(11) NOT NULL DEFAULT '0',
  `viz_y` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`level_id`,`position_id`),
  KEY `graph_nodes_node_type_id_fk` (`node_type_id`),
  CONSTRAINT `graph_nodes_node_type_id_fk` FOREIGN KEY (`node_type_id`) REFERENCES `graph_node_type` (`node_type_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `graph_nodes`
--

LOCK TABLES `graph_nodes` WRITE;
/*!40000 ALTER TABLE `graph_nodes` DISABLE KEYS */;
INSERT INTO `graph_nodes` VALUES (-1,-1,0,0,0),(1,100100,2,100,100),(1,100400,2,100,400),(1,200200,0,200,200),(1,200300,0,200,330),(1,250250,1,250,250),(1,250400,3,250,400),(1,300200,0,300,200),(1,300300,0,300,300),(1,400100,2,400,100),(1,400400,2,400,400);
/*!40000 ALTER TABLE `graph_nodes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ipc_queue`
--

DROP TABLE IF EXISTS `ipc_queue`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ipc_queue` (
  `message_id` int(11) NOT NULL AUTO_INCREMENT,
  `sender` varchar(32) NOT NULL,
  `receiver` varchar(32) NOT NULL,
  `message` varchar(1024) NOT NULL,
  `created` timestamp NULL DEFAULT NULL,
  `received` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`message_id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ipc_queue`
--

LOCK TABLES `ipc_queue` WRITE;
/*!40000 ALTER TABLE `ipc_queue` DISABLE KEYS */;
INSERT INTO `ipc_queue` VALUES (1,'ORDERDISPATCHER','SHUTTLEMANAGER','new order assigned',NULL,NULL),(2,'ORDERDISPATCHER','SHUTTLEMANAGER','new order assigned',NULL,NULL);
/*!40000 ALTER TABLE `ipc_queue` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `job_state`
--

DROP TABLE IF EXISTS `job_state`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `job_state` (
  `job_state_id` int(11) NOT NULL,
  `token` varchar(32) NOT NULL,
  `description` varchar(1024) DEFAULT NULL,
  PRIMARY KEY (`job_state_id`),
  UNIQUE KEY `job_state_token_uindex` (`token`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `job_state`
--

LOCK TABLES `job_state` WRITE;
/*!40000 ALTER TABLE `job_state` DISABLE KEYS */;
INSERT INTO `job_state` VALUES (1,'NEW','This is a brand new job'),(2,'STARTED','This job is already started'),(3,'DONE','This job has been finished successfully'),(4,'CANCELLED','This job has been cancelled for whatever reason');
/*!40000 ALTER TABLE `job_state` ENABLE KEYS */;
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
INSERT INTO `job_type` VALUES (1,'PARK','Park job'),(2,'GET','Load a tote'),(3,'PUT','Unload a tote'),(4,'WAIT','Wait for an action to be finished from outside');
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
  `job_state_id` int(11) NOT NULL DEFAULT '0',
  `level_id` int(11) DEFAULT NULL,
  `position_id` int(11) DEFAULT NULL,
  `sequence` int(11) DEFAULT NULL,
  `start_time` int(11) DEFAULT '0',
  `end_time` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`job_id`),
  KEY `jobs_order_id_fk` (`order_id`),
  KEY `jobs_shuttles_shuttle_id_fk` (`shuttle_id`),
  KEY `jobs_job_type_job_type_id_fk` (`job_type_id`),
  KEY `jobs_job_state_job_state_id_fk` (`job_state_id`),
  CONSTRAINT `jobs_job_state_job_state_id_fk` FOREIGN KEY (`job_state_id`) REFERENCES `job_state` (`job_state_id`),
  CONSTRAINT `jobs_job_type_job_type_id_fk` FOREIGN KEY (`job_type_id`) REFERENCES `job_type` (`job_type_id`),
  CONSTRAINT `jobs_order_id_fk` FOREIGN KEY (`order_id`) REFERENCES `orders` (`order_id`) ON DELETE CASCADE,
  CONSTRAINT `jobs_shuttles_shuttle_id_fk` FOREIGN KEY (`shuttle_id`) REFERENCES `shuttles` (`shuttle_id`)
) ENGINE=InnoDB AUTO_INCREMENT=171 DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `jobs`
--

LOCK TABLES `jobs` WRITE;
/*!40000 ALTER TABLE `jobs` DISABLE KEYS */;
INSERT INTO `jobs` VALUES (13,10,2,2,3,1,100100,1,1562743213,0),(14,10,2,3,3,1,400400,2,1562743233,0),(15,11,2,2,3,1,100400,1,1562743263,0),(16,11,2,3,3,1,300300,2,1562743283,0),(17,14,2,2,3,1,100100,1,1562744385,0),(18,14,2,3,3,1,100100,2,1562744405,0),(19,15,2,2,3,1,100100,1,1562744435,0),(20,15,2,3,3,1,100400,2,1562744455,0),(21,16,2,2,3,1,0,1,1562744919,1562744933),(22,16,2,3,3,1,0,2,1562744954,1562744958),(23,17,2,2,3,1,100100,1,1562744974,1562744988),(24,17,2,3,3,1,100400,2,1562744994,1562745008),(25,18,2,2,3,1,100400,1,1562745024,1562745028),(26,18,2,3,3,1,400400,2,1562745034,1562745048),(27,19,2,2,3,1,100100,1,1562745134,1562745148),(28,19,2,3,3,1,100400,2,1562745154,1562745168),(29,20,2,2,3,1,100400,1,1562745194,1562745198),(30,20,2,3,3,1,200300,2,1562745204,1562745218),(31,21,2,2,3,1,200300,1,1562745244,1562745248),(32,21,2,3,3,1,200200,2,1562745254,1562745268),(33,22,2,2,3,1,200300,1,1562746085,1562746099),(34,22,2,3,3,1,100100,2,1562746105,1562746119),(35,23,2,2,3,1,100100,1,1562746145,1562746149),(36,23,2,3,3,1,400400,2,1562746155,1562746169),(37,24,2,2,3,1,100100,1,1562746486,1562746500),(38,24,2,3,3,1,400400,2,1562746506,1562746520),(39,25,2,2,3,1,400400,1,1562746536,1562746540),(40,25,2,3,3,1,400100,2,1562746546,1562746560),(41,26,2,2,3,1,400100,1,1562746586,1562746590),(42,26,2,3,3,1,200200,2,1562746596,1562746610),(43,27,2,2,3,1,200200,1,1562746626,1562746630),(44,27,2,3,3,1,200300,2,1562746636,1562746650),(45,28,2,2,3,1,200300,1,1562746666,1562746670),(46,28,2,3,3,1,200200,2,1562746676,1562746690),(47,29,2,2,3,1,100100,1,1562746937,1562746951),(48,29,2,3,3,1,100400,2,1562746957,1562746971),(49,30,2,2,3,1,100100,1,1562746987,1562747001),(50,30,2,3,3,1,200200,2,1562747007,1562747021),(51,31,2,2,3,1,200200,1,1562747037,1562747041),(52,31,2,3,3,1,200300,2,1562747047,1562747061),(53,32,2,2,3,1,200300,1,1562860574,1562860578),(54,32,2,3,3,1,300300,2,1562860584,1562860598),(55,33,2,2,3,1,300300,1,1562860614,1562860618),(56,33,2,3,3,1,300200,2,1562860624,1562860638),(57,34,2,2,3,1,300200,1,1562860654,1562860658),(58,34,2,3,3,1,200200,2,1562860664,1562860678),(59,35,2,2,3,1,200200,1,1562860694,1562860698),(60,35,2,3,3,1,100100,2,1562860705,1562860719),(61,36,2,2,3,1,100100,1,1562860735,1562860739),(62,36,2,3,3,1,200200,2,1562860745,1562860759),(63,37,2,2,3,1,100100,1,1563011255,1563011269),(64,37,2,3,3,1,400400,2,1563011275,1563011289),(65,38,2,2,3,1,400400,1,1563011305,1563011309),(66,38,2,3,3,1,400100,2,1563011315,1563011329),(67,39,2,2,3,1,400100,1,1563011365,1563011369),(68,39,2,3,3,1,200200,2,1563011375,1563011389),(69,40,2,2,3,1,100100,1,1563023300,1563023314),(70,40,2,3,3,1,100400,2,1563023320,1563023334),(71,41,2,2,3,1,100400,1,1563023421,1563023423),(72,41,2,3,3,1,400400,2,1563023432,1563023441),(73,42,2,2,3,1,400400,1,1563023662,1563023664),(74,42,2,3,3,1,200300,2,1563023672,1563023681),(75,43,2,2,3,1,100100,1,1563023782,1563023791),(76,43,2,3,3,1,400400,2,1563023792,1563023801),(77,44,2,2,3,1,100100,1,1563036058,1563036067),(78,44,2,3,3,1,400400,2,1563036068,1563036077),(84,51,1,1,3,1,100100,NULL,1563806532,1563806541),(85,52,2,1,3,1,100100,NULL,1563787159,1563787168),(86,53,1,1,3,1,100100,NULL,1563806542,1563806544),(87,54,2,1,3,1,100100,NULL,1563787169,1563787171),(88,55,1,1,3,1,100100,NULL,1563806567,1563806569),(89,56,2,1,3,1,100100,NULL,1563791652,1563791654),(90,57,1,1,3,1,100100,NULL,1563806577,1563806579),(91,58,2,1,3,1,100100,NULL,1563806532,1563806534),(92,59,1,1,3,1,100100,NULL,1563806587,1563806589),(93,60,2,1,3,1,100100,NULL,1563806542,1563806544),(94,61,1,1,3,1,100100,NULL,1563806587,1563806589),(95,62,2,1,3,1,100100,NULL,1563806567,1563806569),(96,63,1,1,3,1,100100,NULL,1563806587,1563806589),(97,65,2,2,3,1,100100,1,1563806577,1563806579),(98,65,2,3,3,1,200200,2,1563806587,1563806596),(99,66,1,1,3,1,100100,NULL,1563806809,1563806811),(100,67,2,1,3,1,100100,NULL,1563810862,1563810871),(101,68,3,1,3,1,100100,NULL,1563810862,1563810871),(102,69,4,1,3,1,100100,NULL,1563810862,1563810871),(103,70,5,1,3,1,100100,NULL,1563810862,1563810871),(104,71,2,2,3,1,200200,1,1563811362,1563811371),(105,71,2,3,3,1,200300,2,1563811372,1563811381),(106,72,2,1,3,1,100100,NULL,1563811403,1563811412),(107,73,2,2,3,1,400400,1,1563811433,1563811442),(108,73,2,3,3,1,0,2,1563811443,1563811452),(109,74,2,2,3,1,400400,1,1563811473,1563811482),(110,74,2,3,3,1,400100,2,1563811483,1563811492),(111,75,2,1,3,1,100100,NULL,1563811523,1563811532),(112,76,2,2,3,1,400400,1,1563811783,1563811792),(113,76,2,3,3,1,400100,2,1563811793,1563811802),(114,77,2,1,3,1,100100,NULL,1563812114,1563812123),(115,78,2,2,3,1,400400,1,1563812171,1563812180),(116,78,2,3,3,1,400100,2,1563812181,1563812190),(117,79,2,1,3,1,100100,NULL,1563812271,1563812280),(118,80,2,2,3,1,400400,1,1563812351,1563812360),(119,80,2,3,3,1,400100,2,1563812361,1563812370),(120,81,2,1,3,1,100100,NULL,1563812381,1563812390),(121,82,2,2,3,1,400400,1,1563812452,1563812461),(122,82,2,3,3,1,400100,2,1563812462,1563812471),(123,83,2,1,3,1,100100,NULL,1563812492,1563812501),(124,84,2,2,3,1,400400,1,1563812692,1563812701),(125,84,2,3,3,1,400100,2,1563812702,1563812711),(126,85,2,1,3,1,100100,NULL,1563812742,1563812751),(127,86,2,2,3,1,400400,1,1563814013,1563814022),(128,86,2,3,3,1,400100,2,1563814041,1563814050),(129,87,2,1,3,1,100100,NULL,1563814061,1563814070),(130,88,2,2,3,1,400400,1,1563814101,1563814110),(131,88,2,3,3,1,400100,2,1563814111,1563814120),(132,89,2,1,3,1,100100,NULL,1563814131,1563814140),(133,90,2,2,3,1,300200,1,1563814151,1563814160),(134,90,2,3,3,1,200200,2,1563814161,1563814170),(135,91,2,1,3,1,100100,NULL,1563814181,1563814190),(136,92,2,2,3,1,100100,1,1563814544,1563814546),(137,92,2,3,3,1,100400,2,1563814554,1563814563),(138,93,2,2,3,1,100400,1,1563814574,1563814576),(139,93,2,3,3,1,400400,2,1563814584,1563814593),(140,94,2,1,3,1,100100,NULL,1563814604,1563814613),(141,95,2,2,3,1,100100,1,1563814734,1563814736),(142,95,2,3,3,1,200200,2,1563814744,1563814753),(143,96,2,2,3,1,200200,1,1563814764,1563814766),(144,96,2,3,3,1,200300,2,1563814774,1563814783),(145,97,2,2,3,1,200300,1,1563814794,1563814796),(146,97,2,3,3,1,300300,2,1563814804,1563814813),(147,98,1,2,3,1,300300,1,1563814814,1563814823),(148,98,1,3,3,1,200300,2,1563814825,1563814834),(149,99,2,1,3,1,100100,NULL,1563814825,1563814834),(150,100,1,1,3,1,100100,NULL,1563814845,1563814854),(151,101,1,2,3,1,100100,1,1563814875,1563814877),(152,101,1,3,3,1,400100,2,1563814885,1563814894),(153,102,2,2,3,1,100100,1,1563814885,1563814887),(154,102,2,3,3,1,400400,2,1563814895,1563814904),(155,103,1,1,3,1,100100,NULL,1563814905,1563814914),(156,104,2,1,3,1,100100,NULL,1563814915,1563814924),(157,105,1,2,3,1,100100,1,1563814965,1563814967),(158,105,1,3,3,1,400400,2,1563814975,1563814984),(159,106,2,2,3,1,100100,1,1563814975,1563814977),(160,106,2,3,3,1,400100,2,1563814985,1563814994),(161,107,1,2,3,1,100100,1,1563814995,1563815004),(162,107,1,3,3,1,300300,2,1563815005,1563815014),(163,108,2,2,3,1,100100,1,1563815005,1563815014),(164,108,2,3,3,1,200200,2,1563815015,1563815024),(165,109,1,1,3,1,100100,NULL,1563815025,1563815034),(166,110,2,1,3,1,100100,NULL,1563815035,1563815044),(167,111,1,2,3,1,100100,1,1563827705,1563827707),(168,111,1,3,2,1,400100,2,1571695359,1571695368),(169,112,2,2,3,1,100100,1,1563827705,1563827707),(170,112,2,3,2,1,400400,2,1571695359,1571695368);
/*!40000 ALTER TABLE `jobs` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `order_state`
--

DROP TABLE IF EXISTS `order_state`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `order_state` (
  `order_state_id` int(11) NOT NULL,
  `token` varchar(32) NOT NULL,
  `description` varchar(1024) DEFAULT NULL,
  PRIMARY KEY (`order_state_id`),
  UNIQUE KEY `order_state_token_uindex` (`token`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `order_state`
--

LOCK TABLES `order_state` WRITE;
/*!40000 ALTER TABLE `order_state` DISABLE KEYS */;
INSERT INTO `order_state` VALUES (1,'NEW','Order is new'),(2,'ASSIGNED','Order is assigned to a shuttle'),(3,'STARTED','A shuttle is actively working on this order'),(4,'DONE','Order has been finished sucessfully'),(5,'CANCELLED','Order has been cancelled for any reason');
/*!40000 ALTER TABLE `order_state` ENABLE KEYS */;
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
INSERT INTO `order_type` VALUES (1,'TRANSPORT','Transport a loading unit'),(2,'PARK','Wait for further orders'),(3,'PROCESS','Some processing of a loading unit will be done at the target station');
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
  `shuttle_id` int(11) DEFAULT NULL,
  `order_state_id` int(11) NOT NULL DEFAULT '1',
  `priority` int(11) NOT NULL,
  `sequence` int(11) NOT NULL DEFAULT '1',
  PRIMARY KEY (`order_id`),
  KEY `orders_order_type_order_type_id_fk` (`order_type_id`),
  KEY `orders_order_state_order_state_id_fk` (`order_state_id`),
  CONSTRAINT `orders_order_state_order_state_id_fk` FOREIGN KEY (`order_state_id`) REFERENCES `order_state` (`order_state_id`),
  CONSTRAINT `orders_order_type_order_type_id_fk` FOREIGN KEY (`order_type_id`) REFERENCES `order_type` (`order_type_id`)
) ENGINE=InnoDB AUTO_INCREMENT=113 DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `orders`
--

LOCK TABLES `orders` WRITE;
/*!40000 ALTER TABLE `orders` DISABLE KEYS */;
INSERT INTO `orders` VALUES (10,1,1,4,10,0),(11,1,2,4,10,0),(14,1,1,4,10,0),(15,1,2,4,10,0),(16,1,2,4,10,0),(17,1,2,4,10,0),(18,1,2,4,10,0),(19,1,2,4,10,0),(20,1,2,4,10,0),(21,1,2,4,10,0),(22,1,2,4,10,0),(23,1,2,4,10,0),(24,1,2,4,10,0),(25,1,2,4,10,0),(26,1,2,4,10,0),(27,1,2,4,10,0),(28,1,2,4,10,0),(29,1,2,4,10,0),(30,1,2,4,10,0),(31,1,2,4,10,0),(32,1,2,4,10,0),(33,1,2,4,10,0),(34,1,2,4,10,0),(35,1,2,4,10,0),(36,1,2,4,10,0),(37,1,2,4,10,0),(38,1,2,4,10,0),(39,1,2,4,10,0),(40,1,2,4,10,0),(41,1,2,4,10,0),(42,1,2,4,10,0),(43,1,2,4,10,0),(44,1,2,4,10,0),(45,2,1,4,0,1),(46,2,1,4,0,1),(47,2,1,4,0,1),(48,2,1,4,0,1),(49,2,1,4,0,1),(50,2,1,4,0,1),(51,2,1,4,0,1),(52,2,2,4,0,1),(53,2,1,4,0,1),(54,2,2,4,0,1),(55,2,1,4,0,1),(56,2,2,4,0,1),(57,2,1,4,0,1),(58,2,2,4,0,1),(59,2,1,4,0,1),(60,2,2,4,0,1),(61,2,1,4,0,1),(62,2,2,4,0,1),(63,2,1,4,0,1),(65,1,2,4,9,0),(66,2,1,4,0,1),(67,2,2,4,0,1),(68,2,3,4,0,1),(69,2,4,4,0,1),(70,2,5,4,0,1),(71,1,2,4,10,0),(72,2,2,4,0,1),(73,1,2,4,10,0),(74,1,2,4,10,0),(75,2,2,4,0,1),(76,1,2,4,10,0),(77,2,2,4,0,1),(78,1,2,4,10,0),(79,2,2,4,0,1),(80,1,2,4,10,0),(81,2,2,4,0,1),(82,1,2,4,10,0),(83,2,2,4,0,1),(84,1,2,4,10,0),(85,2,2,4,0,1),(86,1,2,4,10,0),(87,2,2,4,0,1),(88,1,2,4,10,0),(89,2,2,4,0,1),(90,1,2,4,10,0),(91,2,2,4,0,1),(92,1,2,4,10,0),(93,1,2,4,10,0),(94,2,2,4,0,1),(95,1,2,4,10,0),(96,1,2,4,10,0),(97,1,2,4,10,0),(98,1,1,4,10,0),(99,2,2,4,0,1),(100,2,1,4,0,1),(101,1,1,4,10,0),(102,1,2,4,10,0),(103,2,1,4,0,1),(104,2,2,4,0,1),(105,1,1,4,10,0),(106,1,2,4,10,0),(107,1,1,4,10,0),(108,1,2,4,10,0),(109,2,1,4,0,1),(110,2,2,4,0,1),(111,1,1,3,10,0),(112,1,2,3,10,0);
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
INSERT INTO `shuttle_battery_level` VALUES (0,'UNKNOWN','Shuttle did not transmit its battery charge'),(1,'CRITICAL','Shuttle immediatly needs to be charged and cannot finish its current orders'),(2,'LOW','Shuttle battery is low (shuttle can still finish its current orders)'),(3,'NORMAL','Shuttle battery is sufficiently charged'),(4,'HIGH','Shuttle battery is fully charged');
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
INSERT INTO `shuttle_type` VALUES (0,0,'INVALID','Dummy default value'),(1,1,'ALPEN_SHUTTLE','Alpen shuttle with LAM for 10 loading units'),(2,1,'OPEN_SHUTTLE_50','OS50 with LAM for 1 loading unit');
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
INSERT INTO `shuttles` VALUES (1,2,2,1,3,1,100100),(2,2,2,1,3,1,100100),(3,2,0,1,0,1,100100),(4,2,0,1,0,1,100100),(5,2,0,1,0,1,100100);
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
INSERT INTO `station_type` VALUES (1,'CONVEYOR','Conveyor endpoint'),(2,'MANUAL','Virtual station for manual delivery');
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
INSERT INTO `stations` VALUES (1,2,1,1,100,3),(61,1,1,1,200,1);
/*!40000 ALTER TABLE `stations` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `telegrams`
--

DROP TABLE IF EXISTS `telegrams`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `telegrams` (
  `telegram_id` int(11) NOT NULL AUTO_INCREMENT,
  `sender` varchar(32) NOT NULL,
  `receiver` varchar(32) NOT NULL,
  `state` int(11) NOT NULL DEFAULT '0',
  `message` varchar(2048) DEFAULT NULL,
  PRIMARY KEY (`telegram_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `telegrams`
--

LOCK TABLES `telegrams` WRITE;
/*!40000 ALTER TABLE `telegrams` DISABLE KEYS */;
/*!40000 ALTER TABLE `telegrams` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-12-10 23:55:42
