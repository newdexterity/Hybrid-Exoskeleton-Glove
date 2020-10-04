import pandas as pd
import numpy as np
from sklearn.ensemble import RandomForestClassifier
from sklearn.ensemble import RandomForestRegressor, AdaBoostRegressor
import math
import pickle
import statistics
import sklearn as sk
from sklearn import preprocessing
from pandas import read_csv
import os


class ProcessData:

	# Constructor for data processing
	def __init__(self, filenames, data_split, frequency, data_end_drop):
		home = os.path.expanduser("~")
		self.path = os.path.join(home, 'experiments', 'gusb_amp')
		# CSV Attributes
		self.filenames = filenames
		print(self.filenames)
		self.df = None

		# Data Attributes
		self.data = None
		self.train = None
		self.test = None

		# Classification
		self.grasp = 0

		# Regression
		# self.grasp_set = 0
		self.split = data_split
		self.freq = frequency
		self.drop = data_end_drop

	def add_file_extension(self, filename):
		name = filename.split('.csv')[0] + '.csv'
		print(name)
		return name

	def read_data_classification(self):
		# Loops through CSV's for each grasp type
		file_counter = 0
		for i in self.filenames:
			filename = self.add_file_extension(i)
			path = os.path.join(self.path, filename)

			# Uses pandas library to read csv files, then converted to numpy 2D arrays
			self.df = pd.read_csv(path, index_col=None, header=0)
			self.data = self.df.values

			# Labels and emg channel data extracted from data,
			# reshaped in needed, and combined
			labels = self.data[:, -2] * (file_counter + 1)
			labels = np.reshape(labels, [len(labels), 1])
			# Last Col is Label
			emg_channels = self.data[:, :-2]
			self.data = np.concatenate((emg_channels, labels), 1)

			# Splits data files in testing and training based on input parameters
			drop_idx = ((len(self.data)) - (self.freq * self.drop))

			# Creates then concatenates each grasp file training and testing dataset
			# Checks if current file should be in training or testing set
			# If it is the first file training (or testing) file, create one
			# If not, concatenate the current file with the existing training (or testing) set
			if file_counter <= (self.split - 1):

				if self.train is None:
					self.train = self.data[0:drop_idx, :]
					print("data shape (first)", self.data.shape)

				else:
					self.train = np.concatenate((self.train, self.data[0:drop_idx, :]), 0)
					print("data shape (later)", self.data.shape)
					print("train shape (later)", self.train.shape)

			elif self.test is None:
				self.test = self.data[0:drop_idx, :]
				print(self.data.shape)

			else:
				self.test = np.concatenate((self.test, self.data[0:drop_idx, :]), 0)

			# Increments file counter
			file_counter = file_counter + 1
		# df = pd.DataFrame(data=self.train)
		# df.to_csv('test.csv', index=False)


class Classifiers:

	# Constructor for Classifier (data set)
	def __init__(self, grasps, split=2, frequency=1200, data_end_drop=2, num_trees=100, name=None):

		# Processes dataset
		self.p = ProcessData(grasps, split, frequency, data_end_drop)
		self.p.read_data_classification()
		self.name = name
		# Parameters
		self.clf = None
		self.rf_prediction = None
		self.accuracy = None
		self.trees = num_trees

		# Actions
		self.random_forest_train()
		# self.random_forest_test()

	# Random forest classification training
	def random_forest_train(self):

		# Create a Gaussian Classifier
		self.clf = RandomForestClassifier(n_estimators=self.trees)

		# Train the model using the training sets y_pred=clf.predict(X_test)
		print("Training Model")
		self.clf.fit(self.p.train[:, 0:-1], self.p.train[:, -1])

		filename = self.name.split('.')[0] + '.sav'
		pickle.dump(self.clf, open(filename, 'wb'))

	# Random forest classification testing
	def random_forest_test(self):

		# Prediction step
		self.rf_prediction = self.clf.predict(self.p.test[:, 0:-1])
		counter = 0

		# Calculates overall match accuracy (score equivalent)
		for i in range(len(self.p.test)):
			if self.rf_prediction[i] == self.p.test[i, 8]:
				counter = counter + 1
		self.accuracy = float(counter / (len(self.p.test)))
		# print(self.accuracy)


r = Classifiers((['rest.csv', 'pinch.csv', 'power.csv', 'tripod.csv']), split=10, data_end_drop=0, num_trees=100, name='gesture_classifier')
