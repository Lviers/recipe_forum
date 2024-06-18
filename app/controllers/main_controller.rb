class MainController < ApplicationController
  def index
  end

  def login
  end

  def authenticate
    user = User.find_by(username: params[:username], password: params[:password])

    if user
      redirect_to dashboard_path
    else
      flash[:alert] = 'Invalid username or password'
      redirect_to login_path
    end
  end

  def register
    @user = User.new
  end

  def create_user
    @user = User.new(user_params)

    if @user.save
      redirect_to login_path
    else
      render :register
    end
  end

  def dashboard
  end

  private

  def user_params
    params.require(:user).permit(:username, :password)
  end
end
