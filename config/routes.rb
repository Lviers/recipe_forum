Rails.application.routes.draw do
  root 'main#index'

  get '/login', to: 'main#login'
  post '/authenticate', to: 'main#authenticate'
  get '/register', to: 'main#register'
  post '/create_user', to: 'main#create_user'
  get '/dashboard', to: 'main#dashboard'
end
