from django.db import models

class Album(models.Model):
    title = models.CharField(max_length=100)
    description = models.TextField()

class Photo(models.Model):
    album = models.ForeignKey(Album, on_delete=models.CASCADE)
    image = models.ImageField(upload_to='photos/')
    caption = models.CharField(max_length=250, blank=True)
    place = models.CharField(max_length=250, blank=True)

class User(models.Model):
    name = models.CharField(max_length=100)