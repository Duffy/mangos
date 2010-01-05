DROP TABLE IF EXISTS `mail_external`;
CREATE TABLE `mail_external` (
  `id` int(20) UNSIGNED NOT NULL AUTO_INCREMENT,
  `receiver` bigint(20) UNSIGNED NOT NULL,
  `subject` varchar(200) DEFAULT 'Support Message',
  `message` varchar(500) DEFAULT 'Support Message',
  `money` int(20) UNSIGNED NOT NULL DEFAULT '0',
  `item` int(20) UNSIGNED NOT NULL DEFAULT '0',
  `item_count` int(20) UNSIGNED NOT NULL DEFAULT '1',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;