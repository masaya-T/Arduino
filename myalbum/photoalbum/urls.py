from django.urls import path
from .views import album_list, album_detail, photo_upload

urlpatterns = [
    path('', album_list, name='album_list'),
    path('album/<int:pk>/', album_detail, name='album_detail'),
    path('upload/', photo_upload, name='photo_upload'),
]
